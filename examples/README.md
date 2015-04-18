examples
========

## blendish_example
Is the original C example ported to mruby.

In order to get the same (about 90% the same), I recommend using my Crand
gem to use the C stdlib rand function, otherwise, the OUI::WRAP will look
different using ruby's random generator.
