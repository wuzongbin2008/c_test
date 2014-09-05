#include <libconfig.h>

config_t cfg;

void read_config_file()
{
    int i;
    char *title;
    struct config_setting_t *settings = 0;
    struct config_setting_t *elem = 0;

    config_init(&cfg);
    config_read_file(&cfg,"./ec_notfs.conf");

    if (!(settings = config_lookup(&cfg, "application"))) {
        printf("not found");
    }

    printf("len = %d\n",config_setting_length(settings));
    elem = config_setting_get_elem(settings, 0);
    title = config_setting_get_string_elem(elem,"title");

    for (i = 0; i < config_setting_length(settings); i++) {

        if (elem= config_setting_get_elem(settings, i)) {
            printf("%d name = %s\n", i,elem->name);
        }

    }
}
