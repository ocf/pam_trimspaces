#define PAM_SM_AUTH
#include <security/pam_modules.h>
#include <string.h>


PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    const char *user;
    int ret;

    ret = pam_get_item(pamh, PAM_USER, (const void **) &user);
    if (ret != PAM_SUCCESS) {
        return PAM_AUTH_ERR;
    }

    if (user == NULL) {
        return PAM_SUCCESS;
    }

    size_t len = strlen(user);
    char copy[len + 1];
    char *new_user = copy;
    memcpy(copy, user, len + 1);

    // strip trailing spaces
    for (int i = len - 1; i >= 0; i--) {
        if (copy[i] != ' ') {
            break;
        }
        copy[i] = '\0';
    }

    // strip leading spaces
    for (int i = 0; i < len; i++) {
        if (copy[i] != ' ') {
            break;
        }
        new_user = &copy[i + 1];
    }

    ret = pam_set_item(pamh, PAM_USER, new_user);
    if (ret != PAM_SUCCESS) {
        return PAM_AUTH_ERR;
    }

    return PAM_SUCCESS;
}


PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}
