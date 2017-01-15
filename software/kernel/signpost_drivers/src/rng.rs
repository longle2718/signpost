use kernel::{AppId, AppSlice, Container, Callback, Shared, Driver};
use kernel::common::take_cell::TakeCell;
use kernel::hil;
use kernel::hil::rng;
use core::cmp;
use core::cell::Cell;

struct AppState {
    callback: Cell<Option<Callback>>,
    buffer: TakeCell<AppSlice<Shared, u8>>,
    num_remaining: usize,
    idx: usize,
}

pub struct SimpleRng<'a, RNG: rng::RNG + 'a> {
    rng: &'a RNG,
    app_state: TakeCell<AppState>,
}

impl<'a, RNG: rng::RNG> SimpleRng<'a, RNG> {
    pub fn new(rng: &'a RNG) -> SimpleRng<'a, RNG> {
        SimpleRng {
            rng: rng,
            app_state: TakeCell::empty(),
        }
    }
}

impl<'a, RNG: rng::RNG> rng::Client for SimpleRng<'a, RNG> {
    fn randomness_available(&self, randomness: &mut Iterator<Item = u32>) -> rng::Continue {
        let mut ret = rng::Continue::Done;
        self.app_state.map(|app_state| {
            let mut remaining = app_state.num_remaining;
            let mut idx = app_state.idx;
            app_state.buffer.map(move |buffer| {
                // Add all available and requested randomness to the app buffer
                // randomness comes in 32 bit iterator, so length is the
                // smallest of the buffer length or the requested randomness
                let read_len = cmp::min(buffer.len(), remaining);

                let d = &mut buffer.as_mut()[0..(read_len)];
                for (i, a) in randomness.enumerate() {
                    for j in 0..4 {
                        if remaining == 0 { break; }
                        d[idx] = ((a >> j*8) & 0xff) as u8;
                        idx += 1;
                        remaining -= 1;
                    }
                }
                //panic!("randomness available {} {} {} {}\n", d[0], d[1], d[2], d[3]);
            });
            app_state.num_remaining = remaining;
            app_state.idx = idx;
            if app_state.num_remaining != 0 { ret = rng::Continue::More }
            else {
              app_state.callback.get().map(|mut cb| {
                  cb.schedule(0, 0, 0);
              });
            }
        });
        ret
    }
}

impl<'a, RNG: rng::RNG> Driver for SimpleRng<'a, RNG> {
    fn allow(&self, appid:AppId, allow_num: usize, slice: AppSlice<Shared, u8>) -> isize {
        // pass buffer in from application
        match allow_num {
            0 => {
                let appst = match self.app_state.take() {
                    None => {
                        AppState {
                            callback: Cell::new(None),
                            buffer: TakeCell::new(slice),
                            num_remaining: 0,
                            idx: 0,
                        }
                    }
                    Some(appst) => {
                        appst.buffer.replace(slice);
                        appst
                    }
                };
                self.app_state.replace(appst);
                0
            }
            _ => -1,
        }
    }

    fn command(&self, command_num: usize, data: usize, _: AppId) -> isize {
        match command_num {
            0 => {
                self.app_state.map(|app_state| {
                    app_state.num_remaining = data;
                });
                self.rng.get();
                0
            }
            _ => -1,
        }
    }

    fn subscribe(&self, subscribe_num: usize, callback: Callback) -> isize {
        match subscribe_num {
            0 => {
                let appst = match self.app_state.take() {
                    None => {
                        AppState {
                            callback: Cell::new(Some(callback)),
                            buffer: TakeCell::empty(),
                            num_remaining: 0,
                            idx: 0,
                        }
                    }
                    Some(appst) => {
                        appst.callback.set(Some(callback));
                        appst
                    }
                };
                self.app_state.replace(appst);
                0
            }

            // default
            _ => -1,
        }
    }
}
