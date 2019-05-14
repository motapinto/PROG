#include "utilities.h"

static const char alphanum[] = "0123456789abcdef";

//Feito por Martim
char *salt_generator()
{
    unsigned int rand_val;
    char salt_char;
    static char salt_str[SALT_LEN];
    static unsigned int counter = 0;

    srand(time(NULL) + counter);

    for (int i = 0; i < SALT_LEN; i++) {
        rand_val = rand() % strlen(alphanum);
        salt_char = alphanum[rand_val];

        salt_str[i] = salt_char;
    }
    
    counter++;
    return salt_str;
}

//Feito por Martim
//Feito por Martim
char *sha256sum(const char *pass, const char *salt,char *sha256sum_return)
{
    if(pass==NULL||salt==NULL||sha256sum_return==NULL){
        printf("No sha256sum alguma dos paramentros e NULL\n");
        return NULL;
    }
    
    FILE *fpin;
    char command[MAX_PASSWORD_LEN + SALT_LEN + 21]; //"echo -n (....)  | sha256sum"

    snprintf(command, sizeof(command), "echo -n %s%s | sha256sum", pass, salt);

    //opens fpin
    if ((fpin = popen(command, "r")) == NULL) {
        perror("popen");
    }

    if (fgets(sha256sum_return, HASH_LEN + 1, fpin) == NULL) {
        perror("fgets");
    }

    //close fpin
    if (pclose(fpin) == -1) {
        perror("pclose");
    }
    
    return sha256sum_return;
}

//Feito por Martim
int ignoreSIGPIPE()
{
    sigset_t sigmask;

    //Obter mascara atual
    if (sigprocmask(0, NULL, &sigmask) != 0) {
        perror("sigprocmask");
        exit(SIGPROCMASK_ERROR);
    }

    else {
        //Add to current mask SIGPIPE
        sigaddset(&sigmask, SIGPIPE);
        //Set new mask
        if (sigprocmask(SIG_BLOCK, &sigmask, NULL) != 0) {
            perror("sigprocmask");
            exit(SIGPROCMASK_ERROR);
        }
    }

    return 0;
}

int semaphore_operation(int fd_log, int id, sync_mech_op_t sem_operation, sync_role_t role, int sid, sem_t *semaphore_in_use, const int value_init_sem)
{

    int sem_value;

    if(semaphore_in_use==NULL){
        printf("Passei um semaforo NULL para operation\n");
        return -1;
    }


    if (sem_operation == SYNC_OP_SEM_INIT)
    {
        //Operation de inicializacao de semaforos

        if (logSyncMechSem(fd_log, id, SYNC_OP_SEM_INIT, role, sid, value_init_sem) < 0)
        {
            printf("Erro a registar um sem init no log file do server\n");
        }

        if (sem_init(semaphore_in_use, 0, value_init_sem) != 0)
        {
            perror("Erro a inicializar semaforo");
            return -1;
        }
    }

    else if (sem_operation == SYNC_OP_SEM_WAIT)
    {
        //Operation de Wait de semaforos
        sem_getvalue(semaphore_in_use,&sem_value);

        if (logSyncMechSem(fd_log, id, SYNC_OP_SEM_WAIT, role, sid,sem_value) < 0)
        {
            printf("Erro a registar um sem init no log file do server\n");
        }

        if (sem_wait(semaphore_in_use)!=0)
        {
            perror("Erro a fazer wait do semaforo");
            return -1;
        }
    }
    else if (sem_operation == SYNC_OP_SEM_POST)
    {
        //Operation de Post de semaforos
        
        if(sem_post(semaphore_in_use)!=0){
            perror("Erro a dar post ao semaforo:");
            return -1;
        }

        sem_getvalue(semaphore_in_use,&sem_value);

        if (logSyncMechSem(fd_log, id, SYNC_OP_SEM_POST, role, sid,sem_value) < 0)
        {
            printf("Erro a registar um sem init no log file do server\n");
        }

      
    }
    else
    {
        //Erro
        printf("Erro, na funcao de semaphore_operation. Atingi o else\n");
        perror("Erro nos semaforos:");
        return -1;
    }

    return 0;
}

int mutex_operation(int fd_log, int id, sync_mech_op_t mutex_operation, sync_role_t role, int sid, pthread_mutex_t *mutex_in_use)
{
    if (mutex_operation == SYNC_OP_MUTEX_LOCK)
    {
        //Operation de Lock dos Mutexs

        if(pthread_mutex_lock(mutex_in_use)!=0){
            perror("Erro a dar lock ao mutex:");
            return -1;
        }

        if (logSyncMech(fd_log, id, mutex_operation, role, sid) < 0)
        {   printf("Erro a registar o mutex_lock no log file do server\n");
        }
    }


    else if (mutex_operation == SYNC_OP_MUTEX_UNLOCK)
    {
         if(pthread_mutex_unlock(mutex_in_use)!=0){
            perror("Erro a dar lock ao mutex:");
            return -1;
        }

        if (logSyncMech(fd_log, id, mutex_operation, role, sid) < 0)
        {   printf("Erro a registar o mutex_lock no log file do server\n");
        }




    }
    
    return 0;
}