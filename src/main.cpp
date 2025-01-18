#include "GameClub.h"

// According to the specification, there is no check for the client's presence in the club in the 3 events,
// but I added it because it will be safer this way.
// Why? A person cannot leave the club due to a huge queue if they haven't entered the club in the first place.

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    GameClub gameClub(argv[1]);
    gameClub.start();
    
    getchar();
    return 0;
}
