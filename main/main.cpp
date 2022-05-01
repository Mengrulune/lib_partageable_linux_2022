#include <stdio.h>
#include <string>
#include <iostream>
#include <dlfcn.h>

static int composant(int a, int b, char* lib, char* nom)
{
        int (*com)(int,int);
        int result = 0;
        void *handle;
        
        handle = dlopen(lib, RTLD_LAZY);
        if(!handle)
        {
            printf("%s \n", dlerror());
            exit(1);
        }

        *(void **) (&com) = dlsym(handle, nom);

        if (!com)
        {
            printf("%s \n", dlerror());
            dlclose(handle);
            exit(1);
        }

        result = com(a,b);
        dlclose(handle);
        return result;
}

int main(int argc, char ** argv)
{
	int data1 = 3;
	int data2 = 5;

	int valeur1;
	int valeur2;

	char lib1[] = "./libComposant1.so";
	char lib2[] = "./libComposant2.so";
	
	char nom1[] = "composant1";
	char nom2[] = "composant2";

	valeur1 = composant(data1, data2, lib1, nom1);
	valeur2 = composant(data1, data2, lib2, nom2);

    std::cout << getComposant1Version() << std::endl;
    std::cout << "valeur 1 :" << valeur1 << " valeur 2 :" << valeur2 << std::endl;
    
}
