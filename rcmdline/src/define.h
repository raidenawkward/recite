#ifndef CONSOLE_DEFINE_H
#define CONSOLE_DEFINE_H

// settings
//
//#define SET_CONFIG_FILE_DIR "~/ggst/"
//#define SET_DEFAULT_DICT "/home/raiden/workspace/recite/dictsupport/dict/stardict-langdao-ec-gb-2.4.2/"

#define UI_DEFAULT_RESULT_SPLITER "="
#define UI_DEFAULT_RESULT_SPLITER_LEN 43

// messages
// warnnings
#define MSG_CMD_CHECK_NODICT "no dict input"
#define MSG_CMD_UNKNOWN "unknow parameter"
#define MSG_CMD_ADDUSER_SUCCEED "succeed added user "
#define MSG_CMD_ADDUSER_FAILED "failed to added user "
#define MSG_CMD_SWITCHUSER_SUCCEED "succeed switched to user "
#define MSG_CMD_SWITCHUSER_FAILED "failed switched to user "

// cmds
//
#define CMD_USER "user"
#define CMD_DICT "dict"
#define CMD_CHECK "check"

// user cmds
#define CMD_USER_SHOW_SHORT "-i"
#define CMD_USER_SHOW "--info"
#define CMD_USER_SET_USER_SHORT "-a"
#define CMD_USER_SET_USER "--add"
#define CMD_USER_SWITCH_SHORT "-s"
#define CMD_USER_SWITCH "--switch"
#define CMD_USER_SET_MAIL_SHORT "-m"
#define CMD_USER_SET_MAIL "--mail"
#define CMD_USER_SET_DICT_SHORT "-d"
#define CMD_USER_SET_DICT "--dict"
#define CMD_USER_DEL_USER_SHORT "-D"
#define CMD_USER_DEL_USER "--delete"

// check cmds
#define CMD_CHECK_PHRASE_SHORT "-p"
#define CMD_CHECK_PHRASE "--phrase"
#define CMD_CHECK_WORD_SHORT "-w"
#define CMD_CHECK_WORD "--word"

// error nums
enum RERROR {
	RERROR_NOERROR,
	RERROR_INIT_FAILED,
	RERROR_EXEC_FAILED,
	RERROR_TOO_FEW_PARAMS,
	RERROR_UNKNOWN_PARAM,
};

#endif //CONSOLE_DEFINE_H
