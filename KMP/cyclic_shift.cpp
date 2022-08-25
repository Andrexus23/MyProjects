#include <iostream>
#include "vector"
#include "algorithm"
#include "unordered_map"
using namespace std;

class Solution{
public:
    Solution(string & P, string & T): isShift(P), initial(T){
        if(isShift.size() != initial.size()){
            cout << -1;
        }else {
//            cout << "Мощность: " << alphabet << endl;

//            cout << isShift.size() << " " << initial.size() << " " <<pi.size() << endl;

            string conc = isShift + isShift;
            int res = (int)conc.find(initial);
            cout << res;
//            pi.resize(conc.size());
//            fillPi(conc);
        }
    }
    void fillPi(string & conc){
        int i = 1;
        int j = 0;
        pi[0] = 0;
        if(pi.size() > 1) {
            while (i != pi.size()) {
                if (conc[i] == conc[j]) {
                    pi[i] = j + 1;
                    i++;
                    j++;
                } else if (j == 0) {
                    pi[i] = 0;
                    i++;
                } else {
                    j = pi[j - 1];
                }
            }
        }

        int f = false;
        for(int i = 0; i < pi.size(); i++){
            if(pi[i] == isShift.size()) {
                cout << i - 2 * isShift.size();
                f = true;
                break;
            }
        }
        if(!f) cout << -1;
    }

    void findPattern(){
        int k = 0; int l = 0;

        bool f = false;
        if(initial.size() >= isShift.size()) {
            while (k != initial.size()) {
                if (initial[k] == isShift[l]) {
                    k++;
                    l++;
                    if (l == isShift.size()) {
                        if (!f) {
                            cout << k - l;
                            f = true;
                        }
                        else { cout << "," << k - l; }
                        if (isShift.size() > 1)
                            k = k - l + 1;
                        l = 0;
                    }
                } else if (l == 0) {
                    k++;
                    if (k == initial.size()) break;
                } else {
                    l = pi[l - 1];
                }
            }
        }
        if(!f) cout << -1;
    } //
private:
    string isShift;
    string initial;
    vector<int> pi;
    int alphabet = 0;
};

int main() {
    string P;
    string T;
    cin >> P >> T;
    Solution sol(P, T);
    return 0;
}
