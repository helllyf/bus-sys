#include "led_public.h"
#include <string.h>
#include <stdlib.h>

static char config_1[256];
static char config_2[256];
static char config_3[256];
static char config_4[256];
static char config_5[256];

const char *config_1_text (const char *sInput)
{
    memset (config_1, 0, sizeof (config_1));
    strcpy (config_1, sInput);
    return sInput;
}

const char *config_2_text (const char *sInput)
{
    memset (config_2, 0, sizeof (config_2));
    strcpy (config_2, sInput);
    return sInput;
}

const char *config_3_text (const char *sInput)
{
    memset (config_3, 0, sizeof (config_3));
    strcpy (config_3, sInput);
    return sInput;
}

const char *config_4_text (const char *sInput)
{
    memset (config_4, 0, sizeof (config_4));
    strcpy (config_4, sInput);
    return sInput;
}

const char *config_5_text (const char *sInput)
{
    memset (config_5, 0, sizeof (config_5));
    strcpy (config_5, sInput);
    return sInput;
}

char *_config_1 ()
{
    return config_1;
}

char *_config_2 ()
{
    return config_2;
}

char *_config_3 ()
{
    return config_3;
}

char *_config_4 ()
{
    return config_4;
}

char *_config_5 ()
{
    return config_5;
}

