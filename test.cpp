#include "bigInt.h"
#include "power.h"
#include "gcd.h"
using namespace std;
int main() {
    cout << power(bigInt("53223232"), bigInt("432043294032"), bigInt("323232143243478394738")) << endl;
    cout << gcd(bigInt("4323420493294302439204932043209"), bigInt("60656805960860446067") * bigInt("43829432894328493248329")) << endl;
}
