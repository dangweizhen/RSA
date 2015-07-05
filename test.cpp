#include "bigInt.h"
#include "power.h"
#include "gcd.h"
#include "random.h"
using namespace std;
int main() {
    cout << power(bigInt("53223232"), bigInt("432043294032"), bigInt("323232143243478394738")) << endl;
    cout << gcd(bigInt("4323420493294302439204932043209"), bigInt("60656805960860446067") * bigInt("43829432894328493248329")) << endl;
    cout << inv(bigInt("3"), bigInt("10")) << endl;
    cout << inv(bigInt("3234476509624757991344647769100216810857203198904625400933895331391691459636928060001"), 
                bigInt("265613988875874769338781322035779626829233452653394495974574961739092490901302182994384699044001")) << endl;
    cout << random(10) << endl;
    for (int i = 0; i < 10; i ++) cout << random(512).getnum() << endl;
}
