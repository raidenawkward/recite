#ifndef CONSOLE_DEFINE_H
#define CONSOLE_DEFINE_H

// settings
//
#define SET_CONFIG_FILE_DIR "~/ggst/"
#define SET_DEFAULT_DICT "/home/raiden/workspace/recite/dictsupport/dict/stardict-langdao-ec-gb-2.4.2/"

#define UI_DEFAULT_RESULT_SPLITER "="
#define UI_DEFAULT_RESULT_SPLITER_LEN 43

// messages
// warnnings
#define MSG_CMD_CHECK_NODICT "no dict input"
#define MSG_CMD_UNKNOWN "unknow parameter"

// cmds
//
#define CMD_USER "user"
#define CMD_DICT "dict"
#define CMD_CHECK "check"

// user cmds
#define CMD_USER_SHOW_SHORT "-s"
#define CMD_USER_SHOW "--show"
#define CMD_USER_SET_USER_SHORT "-a"
#define CMD_USER_SET_USER "--add"
#define CMD_USER_SET_MAIL_SHORT "-m"
#define CMD_USER_SET_MAIL "--mail"
#define CMD_USER_SET_DICT_SHORT "-d"
#define CMD_USER_SET_DICT "--dict"
#define CMD_USER_DEL_USER_SHORT "-D"
#define CMD_USER_DEL_USER "--delete"

// error nums
enum RERROR {
	RERROR_NOERROR,
	RERROR_INIT_FAILED,
	RERROR_EXEC_FAILED,
	RERROR_TOO_FEW_PARAMS,
	RERROR_UNKNOWN_PARAM,
};

#endif //CONSOLE_DEFINE_H
