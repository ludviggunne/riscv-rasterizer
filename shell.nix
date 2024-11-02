let
  native = import <nixpkgs> {};
  riscv64 = import <nixpkgs> { crossSystem = { config = "riscv64-none-elf"; }; };
  avr = import <nixpkgs> { crossSystem = { config = "avr"; }; };
in
native.mkShell {
  buildInputs = [
    avr.buildPackages.gcc
    riscv64.buildPackages.gcc
    native.glew
    native.freeglut
    native.avrdude
    native.picocom
  ];
}
