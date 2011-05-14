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
#define MSG_CMD_CHECK_NODICT "warnning : no dict input"


// cmds
//
#define CMD_USER "user"
#define CMD_DICT "dict"
#define CMD_CHECK "check"

// error nums
enum RERROR {
	RERROR_NOERROR,
	RERROR_INIT_FAILED,
	RERROR_EXEC_FAILED,
	RERROR_TOO_FEW_PARAMS
};

#endif //CONSOLE_DEFINE_H
