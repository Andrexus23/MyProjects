#include <iostream>
#include "vector"
#include "algorithm"
#include "unordered_map"
using namespace std;

// Сложность по времени O(m + n), m - длина текста, n - длина искомой подстроки

class Solution{
public:
    Solution(string & P, string & T):pattern(P), text(T){
        if(pattern.size() > text.size()){
            cout << -1;
        }else {
//            cout << "Мощность: " << alphabet << endl;

//            cout << pattern.size() << " " << text.size() << " " <<pi.size() << endl;

            string conc = pattern + "@" + text;
            pi.resize(conc.size());
//            cout << pi.size();
            fillPi(conc);
//            findPattern();
        }
    }
    void fillPi(string & conc){
        int i = 1;
        int j = 0;
        pi[0] = 0;
//        cout << conc << endl;
        if(pi.size() > 1) {
            while (i != pi.size()) {
//                cout << i << " " << j << endl;
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

//        for(int i = 0; i < pi.size(); i++){
//            cout << pi[i] << " ";
//        }
//
        int f = false;
        for(int i = 0; i < pi.size(); i++){
            if(pi[i] == pattern.size()) {
                if(f) cout << "," << i - 2 * pattern.size();
                else {f = true; cout << i - 2*pattern.size();}
            }
        }
        if(!f) cout << -1;
    }

    void findPattern(){
        int k = 0; int l = 0;

        bool f = false;
        if(text.size() >= pattern.size()) {
            while (k != text.size()) {
                if (text[k] == pattern[l]) {
                    k++;
                    l++;
                    if (l == pattern.size()) {
                        if (!f) {
                            cout << k - l;
                            f = true;
                        }
                        else { cout << "," << k - l; }
                        if (pattern.size() > 1)
                            k = k - l + 1;
                        l = 0;
                    }
                } else if (l == 0) {
                    k++;
                    if (k == text.size()) break;
                } else {
                    l = pi[l - 1];
                }
            }
        }
        if(!f) cout << -1;
    }
private:
    string pattern;
    string text;
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
