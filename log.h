extern int /* bool */ EM_anyErrors;
extern int LogTokenPos;

void LogNewLine();
void LogError(int, char *, ...);
void LogImpossible(char *, ...);
void LogReset(char *filename);