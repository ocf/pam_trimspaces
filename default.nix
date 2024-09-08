{ lib, stdenv, pam }:

stdenv.mkDerivation {
  pname = "pam_trimspaces";
  version = "1.0.1ocf1";
  src = ./.;

  buildInputs = [ pam ];

  installPhase = ''
    mkdir -p "$out/lib/security/"
    cp pam_trimspaces.so "$out/lib/security/"
  '';

  meta = with lib; {
    homepage = "https://github.com/ocf/pam_trimspaces";
    description = "PAM module to trim whitespace from usernames";
    platforms = platforms.linux;
  };
}
