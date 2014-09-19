#include <libconfig.h>

config_t cfg;

void read_config_file()
{
    int i,x;
    int b;
    char **s;
    struct config_setting_t *settings = 0;
    struct config_setting_t *elem = 0;

    config_init(&cfg);
    config_read_file(&cfg,"./ec_notfs.conf");

    if (!(settings = config_lookup(&cfg, "application"))) {
        printf("not found");
    }

    //printf("len = %d\n",config_setting_length(settings));
    elem = config_setting_get_elem(settings, 0);
    printf("name = %s\n",elem->name);
    elem = config_setting_get_elem(elem,2);
    printf("name = %s\n",elem->name);
    elem = config_setting_get_elem(elem,1);
    printf("name = %s\n\n",elem->name);

    config_lookup_int(&cfg,"application.window.pos.y",&x);
    printf("x=%d\n",x);

    s = (char **)malloc(sizeof(char)*10);
    config_lookup_string(&cfg,"application.list.[0].[0]",s);
    printf("s=%s\n",*s);
    config_lookup_int(&cfg,"application.list.[0].[1]",&i);
    printf("i=%d\n",i);
    config_lookup_bool(&cfg,"application.list.[0].[2]",&b);
    printf("b=%d\n",b);

    for (i = 0; i < config_setting_length(settings); i++)
    {
        if (elem = config_setting_get_elem(settings, i)) {
            //printf("%d name = %s\n", i,elem->name);
            //printf("%d type = %d\n", i,elem->type);
        }
    }
}
