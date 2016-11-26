#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>

using namespace std;

stack<char> st_final;

bool isoperand(char ch)
{
        int x = int (ch);
        if (x >= 97 && x<=122)
                return true;
        else
                return false;
}

bool isrightbrak(char ch){
        if (ch == ')')
                return true;
        else
                return false;
}

bool isleftbrak(char ch){
        if (ch == '(')
                return true;
        else
                return false;
}

int inorder_postorder(string str){
        stack<char> st;
        int n = str.size();


        for(int i =0; i<n; i++){
                if (isoperand(str[i])){
                        st_final.push(str[i]);
                }

                else if (isrightbrak(str[i])){
                        while (st.top() != '('){
                                st_final.push(st.top());
                                st.pop();
                        }
                        st.pop();
                }
                else if (isleftbrak(str[i]))
                        st.push(str[i]);
                else {
                        /* These Lines would be added for postfix conversion of equations such as
                         * (a+b)*c not for regex
                         */
                        //if (!st.empty() && !isleftbrak(st.top()) && prec(str[i]) > prec(st.top())) {
                        //      st.push(str[i]);
                        //}
                        if(!st.empty() && !isleftbrak(st.top())){
                                st_final.push(st.top());
                                st.pop();
                                st.push(str[i]);
                        }
                        else
                                st.push(str[i]);
                }
        }
        while(!st.empty()){
                st_final.push(st.top());
                st.pop();
        }

        return (st_final.size());

}

struct trans{
	int start_ver;
	int end_ver;
	char input;
};

class nfa {
	public:
	vector<trans> v1;
	int finish_ver;

	nfa(){

	}
	void state_machine(int start, int end, char input){
		trans t1;
		t1.start_ver = start;
		t1.end_ver = end;
		t1.input = input;
		v1.push_back(t1);
		finish_ver = end;
	}
	
	void display() {
		trans t;
		for (int i =0; i<v1.size(); i++){
			t = v1.at(i);
			cout <<"q"<<t.start_ver<<"--->q"<<t.end_ver<<" Input: "<<t.input<<endl;
		}
		cout << "The Accepting State is q"<<t.end_ver<<endl;
	}

};

nfa a_b_concat(nfa a, nfa b){
	trans t1;
	int j =0; 
	nfa a_b;
		
	for(int i =0; i< a.v1.size(); i++){
		a_b.v1.push_back(a.v1[i]);
		j++;
	}
	int k = j+1;
	a_b.state_machine(j, k, '^');
	for(int i =0; i<b.v1.size(); i++){
		t1.start_ver = b.v1[i].start_ver + k;
		t1.end_ver  = b.v1[i].end_ver + k;
		t1.input = b.v1[i].input;
		a_b.v1.push_back(t1);
	}
	a_b.finish_ver = t1.end_ver;
	
	return a_b;
}

nfa a_kleen(nfa b){
	nfa a_kleen;
	trans t1;
	a_kleen.state_machine(0,1,'^');
	int last = b.finish_ver;
	
	for(int i =0; i<b.v1.size(); i++){
		t1.start_ver = b.v1[i].start_ver + 1;
		t1.end_ver  = b.v1[i].end_ver + 1;
		t1.input = b.v1[i].input;
		a_kleen.v1.push_back(t1);
	}
	a_kleen.state_machine(last+1,1,'^');
	a_kleen.state_machine(last+1,last+2,'^');
	a_kleen.state_machine(0,last+2,'^');
	a_kleen.finish_ver = last + 1;
	return a_kleen;
}
		
nfa a_or_b(nfa a, nfa b)
{
	nfa nfa_or;
	trans t1;
	int last_a = a.finish_ver;
	int last_b = b.finish_ver;
	
	nfa_or.state_machine(0,1,'^');
	for(int i =0; i<a.v1.size(); i++){ 
		t1.start_ver = a.v1[i].start_ver + 1;
		t1.end_ver  = a.v1[i].end_ver + 1;
		t1.input = a.v1[i].input;
		nfa_or.v1.push_back(t1);
	}
	nfa_or.state_machine(last_a+1,last_a+2,'^');
	int last = nfa_or.finish_ver;

	nfa_or.state_machine(0,last+1,'^');
	
	for(int i =0; i<b.v1.size(); i++){
		t1.start_ver = b.v1[i].start_ver + last + 1;
		t1.end_ver  = b.v1[i].end_ver + last+ 1;
		t1.input = b.v1[i].input;
		nfa_or.v1.push_back(t1);
	}
	nfa_or.state_machine(t1.end_ver,last,'^');
	nfa_or.finish_ver = last;
	return nfa_or;
}

int main()
{
	nfa a1,b1;
	stack <char> st_s;
	stack <nfa> q;
	string str;
        cout << "Enter the inorder expression"<<endl;
        getline(cin,str);

	int size = inorder_postorder(str);
	
	/*
         * After this loop st_s would contain things in
         * post-fix form
         */
        for (int i =0; i<size; i++) {
                st_s.push(st_final.top());
                st_final.pop();
        }

	for (int i = 0; i<size; i++) {
		char ch = st_s.top();
		if (isoperand(ch)) {
			nfa a2, b2;
			if (ch == 'a'){
				a2.state_machine(0,1,'a');
				q.push(a2);
			}else if(ch == 'b'){
				b2.state_machine(0,1,'b');
				q.push(b2);
			}
		}else if(ch == '.'){
			a1 = q.top();
			q.pop();
			b1 = q.top();
			q.pop();
			q.push(a_b_concat(b1,a1));
		}else if(ch == '*'){
			a1 = q.top();
			q.pop();
			q.push(a_kleen(a1));
		}else {
			 a1 = q.top();
                         q.pop();
                         b1 = q.top();
                         q.pop();
                         q.push(a_or_b(b1,a1));
		}
		st_s.pop();
	}
	
	a1 = q.top();
	a1.display();

return 0;
}

/*
 * Comment out the following area and replace with the main function
 * to see the common working of 'or' 'and' and 'keelne' operations.
*

	//Possible set of Alphabets {a,b}
	nfa a, b;
	
	a.state_machine(0,1,'a');
	b.state_machine(0,1,'b');
	a.display();
	b.display();

	//Concatening case

	nfa a_b = a_b_concat(a, b);
	a_b.display();
	
	nfa a_kleen1 = a_kleen(a);
	a_kleen1.display();
	
	nfa or_func = a_or_b(a,b);
	or_func.display();

	return 0;
}*/
