#include <libconfig.h>

config_t cfg;

void read_config_file()
{
    int i,x;
    char *title;
    struct config_setting_t *settings = 0;
    struct config_setting_t *elem = 0;

    config_init(&cfg);
    config_read_file(&cfg,"./ec_notfs.conf");

    if (!(settings = config_lookup(&cfg, "application"))) {
        printf("not found");
    }

    //printf("len = %d\n",config_setting_length(settings));
    elem = config_setting_get_elem(settings, 0);
    printf("name=%s\n",elem->name);
    elem = config_setting_get_elem(elem,2);
    printf("name=%s\n",elem->name);
    elem = config_setting_get_elem(elem,1);
    printf("name=%s\n",elem->name);
    config_lookup_int(&cfg,"application.window.pos.y",&x);
    printf("x=%d\n",x);
    //printf("title = %d\n\n",config_setting_is_array(eleml));

    for (i = 0; i < config_setting_length(settings); i++)
    {
        if (elem= config_setting_get_elem(settings, i)) {
            //printf("%d name = %s\n", i,elem->name);
            //printf("%d type = %d\n", i,elem->type);
        }
    }
}
