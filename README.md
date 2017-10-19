# pam_trimspaces

[![Build Status](https://jenkins.ocf.berkeley.edu/buildStatus/icon?job=pam_trimspaces/master)](https://jenkins.ocf.berkeley.edu/job/pam_trimspaces/job/master/)

PAM module to trim spaces on both sides of the username. This is useful
especially in login GUIs used by the general computer-illiterate public.

There are some relevant tickets suggesting adding this functionality to lightdm
or other areas, but none so far have significant traction.


## Installation

Either install the Debian package, or somehow plop the `.so` file into place.
Then add to your PAM config file:

```diff
--- /etc/pam.d/lightdm.orig
+++ /etc/pam.d/lightdm
@@ -1,5 +1,8 @@
 #%PAM-1.0

+# Strip leading and trailing whitespace from username
+auth      requisite pam_trimspaces.so
+
 # Block login if they are globally disabled
 auth      requisite pam_nologin.so
```

You can add this to whatever PAM service chain you like, but we choose only to
use it for lightdm (it's much harder to e.g. accidentally log in with spaces in
your name via SSH).


## Building
### Building the `.so` directly

* Run `make`.


### Building the Debian package using Docker

* Run `package_{dist}`, e.g. `package_stretch`.


### Building the Debian package locally

* Use the regular packaging commands to get the desired output. For example, to
  build only a binary package and skip signing, try `debuild -us -uc -b`.
