{
  description = "PAM module to trim whitespace from usernames";

  outputs = { self }: {
    overlays.default = (final: prev: {
      ocf-pam_trimspaces = final.callPackage ./. { };
    });
  };
}
