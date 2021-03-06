#ifndef DEFINES_H
#define DEFINES_H

// record info
#ifdef WIN32
	#define RECORD_CORE_PATH "c:\\ggst\\config"
	#define RECORD_DEFAULT_USER_DIR "c:\\ggst\\users\\"
#else
	#define RECORD_DEFAULT_USER_DIR "/home/raiden/.ggst/users/"
	#define RECORD_CORE_PATH "/home/raiden/.ggst/config"
#endif


// defines for ini
#define INI_KEY_DICT_NAME "dict.name"
#define INI_KEY_DICT_PATH "dict.path"
#define INI_KEY_DICT_MD5 "dict.md5"
#define INI_KEY_DICT_WORDCOUNT "dict.word.count"
#define INI_KEY_DICT_STARTDATE "dict.date.start"

#define INI_KEY_USER_NAME "user.name"
#define INI_KEY_USER_MAIL "user.mail"
#define INI_KEY_USER_REGISTDATE "user.date.regist"
#define INI_KEY_USER_CURRENTDICT "user.dict.current"
#define INI_KEY_USER_DICT_NAME "user.dict.name"

#define INI_KEY_RCORE_USERDIR "rcore.user.dir"
#define INI_KEY_RCORE_CURRENT_USER "core.user.current"


// defines for RDiet
#define RDIET_LIST_KEY "list"



#endif //DEFINES_H
