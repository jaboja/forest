# Las *(The Forest)*
## A generative forest.

The application is split into two separate parts:

 1. **Graphics** (`gfx` directory) – written in C++ with Allegro programming library. Primarily developed on Windows with Visual Studio and then ported to Linux. If you want to recompile it on Windows you may wish to uncomment commented lines of code.
 2. **Sound** (`snd` directory) – a ChucK script which generates a sound background. Should be run with MiniAudicle prior starting graphical part of the piece. Accepts an argument which changes tempo. For best effect I suggest running several instances of the script giving following values as arguments (respectively):
    * 0.333
    * 0.667
    * 1
    * 3
    * 6 or 9
