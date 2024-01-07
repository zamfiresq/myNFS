const LUNGIME_FILENAME = 150;
const LUNGIME_FILEDATA = 1024;

struct cerere {
    string numeFisier<LUNGIME_FILENAME>;
    int startOffset;
};

struct chunk {
    string fisier<LUNGIME_FILENAME>;
    opaque data<LUNGIME_FILEDATA>;
    int dim;
    int destOffset;
};


program MYNFS_RPC {
    version MYNFS_VERSION_1 {
        int MYNFS_OPEN(string) = 1;
        int MYNFS_CLOSE(int) = 2;
        int MYNFS_READ(int) = 3;
        int MYNFS_WRITE(int) = 4;
        int MYNFS_TOUCH(string numeFisier) = 5;
        int MYNFS_RM(string numeFisier) = 6;
        string MYNFS_LS(string) = 7;
        int MYNFS_MKDIR(string numeDir) = 8;
        int MYNFS_RMDIR(string numeDir) = 9;
        int MYNFS_OPENDIR(string numeDir) = 10;
        int MYNFS_READDIR(int) = 11;
        chunk MYNFS_GETCHUNK(cerere*) = 12;

    } = 1;

} = 0x21000001;
