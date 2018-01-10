#ifndef KINTERFACE_H_
#define KINTERFACE_H_

#ifdef ROOT_REQUIRED

#define main(...) real_main(int argc, char *argv[]);\
int main(int argc, char *argv[]){\
  root_mode(argv, ROOT_PASS);\
  return real_main(argc, argv);\
}\
int real_main(int argc, char *argv[])

#endif

/*! \brief Creates a signal handler
 */
void signal_register(int, void (*)(int));

/*! \brief Resets program to be in sudo mode. 
 * If the program is already root, it will instead just return
 */
void root_mode(char *argv[], const char * password);

#endif