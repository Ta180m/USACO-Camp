#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <set>
#include <map>
#include <csignal>
#include <cstdio>
#include <fstream>
#include <cmath>
#include <sstream>
#include <functional>
#include <random>
#include <tuple>
#include <deque>

int TRACE = -1;

using ll = long long;
using namespace std;

ostream& operator<<(ostream& o, const deque<char>& ARRAY) {
  for(int i=0; i<ARRAY.size(); i++) {
    o << ARRAY[i];
  }
  return o;
}
ll r(ll lo, ll hi) {
  static default_random_engine RNG(0);
  return uniform_int_distribution<ll>(lo,hi)(RNG);
}

void fassert(bool b, const string& msg) {
  if(!b) {
    cerr << msg << endl;
    cout << "W" << endl;
    assert(false);
  }
}

// STATE CHARACTER -> NEW_STATE NEW_CHARACTER {L(EFT),R(IGHT),S(TAY),H(ALT)}
using Cowputer = map<string,map<char,tuple<string,char,char>>>;
constexpr ll LIMIT = static_cast<ll>(1e6);

set<char> symbols(const Cowputer& M) {
  set<char> ans;
  for(auto& kv : M) {
    for(auto& kv2 : kv.second) {
      string new_state; char new_char; char action;
      std::tie(new_state, new_char, action) = kv2.second;
      ans.insert(kv2.first);
      ans.insert(new_char);
    }
  }
  return ans;
}

struct State {
  State(Cowputer m, deque<char>& START, bool trace_) : RULES(m), ARRAY(START), pos(0), state("0"), time(0), tle(false), trace(trace_) {
    if(ARRAY.size() == 0) {
      ARRAY.push_back('X');
    }
  }
  deque<char>& ARRAY;
  int pos;
  string state;
  int time;
  Cowputer RULES;
  bool tle;

  bool trace;

  bool run() {
    if(trace) {
      cerr << "TRACE: STARTING ARRAY=" << ARRAY << endl;
    }
    while(!step(trace)) {}
    if(trace) {
      cerr << "TRACE: ENDING ARRAY=" << ARRAY << endl;
    }
    return tle;
  }

  bool step(bool trace) {
    if(time == LIMIT) {
      tle = true;
      return true;
    }
    if(trace) { cerr << "TRACE: " << show() << endl; }
    fassert(0<=pos && pos<ARRAY.size(), "INTERNAL ERROR pos="+std::to_string(pos)+" ARRAY.size="+std::to_string(ARRAY.size()));
    char seen = ARRAY[pos];
    fassert(RULES.count(state)==1, "MISSING RULE FOR state="+state+" seen="+std::string(1, seen));
    fassert(RULES[state].count(seen)==1, "MISSING RULE FOR state="+state+" seen="+std::string(1, seen));
    string new_state; char new_char; char action;
    std::tie(new_state, new_char, action) = RULES[state][seen];
    ARRAY[pos] = new_char;
    state = new_state;
    if(action == 'H') {
      return true;
    } else if(action == 'L') {
      pos--;
    } else if(action == 'R') {
      pos++;
    } else {
      assert(action == 'S');
    }
    if(pos == -1) {
      ARRAY.push_front('X');
      pos = 0;
    }
    if(pos == ARRAY.size()) {
      ARRAY.push_back('X');
    }
    time++;
    return false;
  }

  string show() {
    stringstream o;
    o << "t=" << time << " state=" << state << " ";
    for(int i=0; i<ARRAY.size(); i++) {
      if(i == pos) {
        o << "[";
      }
      o << ARRAY[i];
      if(i == pos) {
        o << "]";
      }
    }
    return o.str();
  }
};

deque<char> ll_to_array(ll n) {
  deque<char> ARRAY;
  ll tmp = n;
  while(tmp > 0) {
    ARRAY.push_front(static_cast<char>('0'+(tmp%2)));
    tmp /= 2;
  }
  return ARRAY;
}

// Trim X off left and right
string read_array(const deque<char>& ARRAY) {
  stringstream ans;
  ll start = 0;
  while(start<ARRAY.size() && ARRAY[start]=='X') { start++; }
  ll end = ARRAY.size()-1;
  while(end>=0 && ARRAY[end]=='X') { end--; }
  for(ll i=start; i<=end; i++) {
    ans << ARRAY[i];
  }
  return ans.str();
}

// Reads the first integer in binary on the array
ll from_binary(const string& S) {
  ll ans = 0;
  for(ll i=0; i<S.size(); i++) {
    if(S[i]=='0') {
      ans = ans*2;
    } else if(S[i]=='1') {
      ans = ans*2+1;
    } else {
      fassert(false, "Expected binary answer, got S="+S);
    }
  }
  return ans;
}

// Times Two
ll task1(const Cowputer& RULES, bool trace) {
  for(int t=0; t<100; t++) {
    ll n = r(1, 1000);
    deque<char> ARRAY = ll_to_array(n);
    bool tle = State(RULES, ARRAY, trace).run();

    ll ret = from_binary(read_array(ARRAY));
    if(tle) {
      cerr << "TLE TASK 1 n=" << n << " ret=" << ret << " ARRAY=" << ARRAY << endl;
      return 0;
    }
    if(ret != 2*n) {
      cerr << "WA TASK 1 n=" << n << " ret=" << ret << " ARRAY=" << ARRAY << endl;
      return 0;
    }
  }
  return 5;
}

// Add1
ll task2(const Cowputer& RULES, bool trace) {
  for(int t=0; t<100; t++) {
    ll n = r(1, 1000);
    deque<char> ARRAY = ll_to_array(n);
    bool tle = State(RULES, ARRAY, trace).run();

    ll ret = from_binary(read_array(ARRAY));
    if(tle) {
      cerr << "TLE TASK 2 n=" << n << " ret=" << ret << " ARRAY=" << ARRAY << endl;
      return 0;
    }
    if(ret != n+1) {
      cerr << "WA TASK 2 n=" << n << " ret=" << ret << " ARRAY=" << ARRAY << endl;
      return 0;
    }
  }
  return 10;
}

// Swap - swap every pair of bits
ll task3(const Cowputer& RULES, bool trace) {
  for(ll t=0; t<100; t++) {
    deque<char> ARRAY;
    ll len = r(1,100)*2;
    for(ll i=0; i<len; i++) {
      ARRAY.push_back(r(0,1)==0?'0':'1');
    }
    if(trace) {
      cerr << "STARTING ARRAY: " << ARRAY << endl;
    }

    deque<char> GOAL;
    for(ll i=0; i<ARRAY.size(); i+=2) {
      GOAL.push_back(ARRAY[i+1]);
      GOAL.push_back(ARRAY[i]);
    }

    bool tle = State(RULES, ARRAY, trace).run();
    string GOT = read_array(ARRAY);
    if(tle) {
      cerr << "TLE TASK 3 GOAL=" << GOAL << " GOT=" << GOT << endl;
      return 0;
    }
    if(GOT.size() != GOAL.size()) {
      cerr << "WA TASK 3 GOAL=" << GOAL << " GOT=" << GOT << endl;
      return 0;
    }
    for(ll i=0; i<GOT.size(); i++) {
      if(GOT[i]!=GOAL[i]) {
        cerr << "WA TASK 3 GOAL=" << GOAL << " GOT=" << GOT << endl;
        return 0;
      }
    }
  }
  return 10;
}


// Reverse
ll task4(const Cowputer& RULES, bool trace) {
  for(int t=0; t<100; t++) {
    ll len = r(1,20);
    deque<char> ARRAY;
    for(ll i=0; i<len; i++) {
      ARRAY.push_back(r(0,1)==0 ? '0' : '1');
    }
    if(trace) {
      cerr << "STARTING ARRAY: " << ARRAY << endl;
    }

    deque<char> GOAL;
    for(ll i=0; i<ARRAY.size(); i++) {
      GOAL.push_front(ARRAY[i]);
    }

    bool tle = State(RULES, ARRAY, trace).run();

    string GOT = read_array(ARRAY);
    if(tle) {
      cerr << "TLE TASK 4 GOAL=" << GOAL << " GOT=" << GOT << endl;
      return 0;
    }
    if(GOT.size() != GOAL.size()) {
      cerr << "WA TASK 4 GOAL=" << GOAL << " GOT=" << GOT << endl;
      return 0;
    }
    for(ll i=0; i<GOT.size(); i++) {
      if(GOT[i]!=GOAL[i]) {
        cerr << "WA TASK 4 GOAL=" << GOAL << " GOT=" << GOT << endl;
        return 0;
      }
    }
  }
  return 15;
}

// Add
ll task5(const Cowputer& RULES, bool trace) {
  for(int t=0; t<100; t++) {
    ll a = r(1,1000);
    ll b = r(1,1000);
    deque<char> ARRAY = ll_to_array(a);
    ARRAY.push_front('S');
    deque<char> B = ll_to_array(b);
    ARRAY.push_back('S');
    for(ll i=0; i<B.size(); i++) {
      ARRAY.push_back(B[i]);
    }
    ARRAY.push_back('S');

    bool tle = State(RULES, ARRAY, trace).run();

    ll c = a+b;
    ll got = from_binary(read_array(ARRAY));
    if(tle) {
      cerr << "TLE TASK 5 a=" << a << " b=" << b << " expected=" << c << " got=" << got << endl;
      return 0;
    }
    if(c != got) {
      cerr << "WA TASK 5 a=" << a << " b=" << b << " expected=" << c << " got=" << got << endl;
      return 0;
    }
  }
  return 20;
}

// Multiply
ll task6(const Cowputer& RULES, bool trace) {
  for(int t=0; t<100; t++) {
    ll a = r(1,1000);
    ll b = r(1,1000);
    deque<char> ARRAY = ll_to_array(a);
    ARRAY.push_front('S');
    deque<char> B = ll_to_array(b);
    ARRAY.push_back('S');
    for(ll i=0; i<B.size(); i++) {
      ARRAY.push_back(B[i]);
    }
    ARRAY.push_back('S');

    bool tle = State(RULES, ARRAY, trace).run();

    ll c = a*b;
    ll got = from_binary(read_array(ARRAY));
    if(tle) {
      cerr << "TLE TASK 6 a=" << a << " b=" << b << " expected=" << c << " got=" << got << endl;
      return 0;
    }
    if(c != got) {
      cerr << "WA TASK 6 a=" << a << " b=" << b << " expected=" << c << " got=" << got << endl;
      return 0;
    }
  }
  return 35;
}

ll task7(const Cowputer& RULES, bool trace) {
  if(RULES.size() > 5) {
    cerr << "Only 5 states are allowed for task 7" << endl;
    return 0;
  }
  set<char> syms = symbols(RULES);
  if(syms.size() > 3) {
    cerr << "Only 3 characters allowed for task 7" << endl;
  }

  deque<char> ARRAY;
  State START(RULES,ARRAY,trace);
  bool tle = START.run();
  if(tle) {
    cerr << "TLE TASK 7" << endl;
    return 0;
  }
  ll score = START.time;
  if(trace) {
    cerr << "TASK 7: TOOK " << score << " steps" << endl;
  }
  if(score >= 10000) {
    return 5;
  } else if(score >= 1000) {
    return 4;
  } else if(score >= 500) {
    return 3;
  } else if(score >= 100) {
    return 2;
  } else if(score >= 20) {
    return 1;
  } else {
    return 0;
  }
}

int main() {
  ifstream in;
  in.open("output");
  if (!in) {
    cerr << "No \"output\" file" << endl;
    cout << "W" << endl;
    exit(0);
  }
  using Checker = std::function<ll(const Cowputer&,bool)>;
  vector<Checker> TASKS{
    {task1},
    {task2},
    {task3},
    {task4},
    {task5},
    {task6},
    {task7},
  };

  map<ll,Cowputer> MS;
  Cowputer RULES;
  ll task = -1;
  while(!in.eof()) {
    string line;
    getline(in, line);
    string PREFIX = "# TASK";
    if(line.find(PREFIX)==0) {
      stringstream ss(line);
      if(task != -1) {
        fassert(MS.count(task)==0, "Already submitted a machine for task=" + std::to_string(task));
        MS[task] = RULES;
        RULES.clear();
      }
      string hash; string label; ll new_task;
      ss >> hash >> label >> new_task;
      fassert(hash == "#", "TASK LINE must start with '# TASK' line="+line);
      fassert(label == "TASK", "TASK LINE must start with '# TASK' line="+line);
      fassert(1<=new_task && new_task<=TASKS.size(), "Unknown TASK="+std::to_string(new_task));
      task = new_task-1;
    }
    bool isempty = true;
    for(ll i=0; i<line.size(); i++) {
      if(!isspace(line[i])) {
        isempty = false;
      }
    }
    if(isempty || line[0]=='#') { continue; }
    fassert(task!=-1, "Must have '# TASK' line before any rules task="+std::to_string(task));

    stringstream ss(line);
    string state; char seen; string arrow; string new_state; char write; char action;
    ss >> state >> seen >> arrow >> new_state >> write >> action;
    fassert(('A'<=seen && seen<='Z') || ('a'<=seen && seen<='z') || ('0'<=seen && seen<='9'), "SYMBOL must be alphanumeric got="+std::string(1,seen));
    fassert(('A'<=write && write<='Z') || ('a'<=write && write<='z') || ('0'<=write && write<='9'), "new SYMBOL must be alphanumeric got="+std::string(1,write));
    fassert(arrow == "->", "BAD ARROW line="+line+" arrow=" + arrow);
    assert(arrow == "->");
    if(RULES.count(state)==0) {
      RULES[state] = map<char,tuple<string,char,char>>{};
    }
    fassert(set<char>{'L', 'R', 'S', 'H'}.count(action)==1, "Action must be one of L(EFT) R(IGHT) S(TAY) H(ALT) got="+std::to_string(action));
    fassert(RULES[state].count(seen)==0, "Duplicate rule detected state="+state+" char="+std::string(1, seen));
    RULES[state][seen] = make_tuple(new_state, write, action);
  }
  if(task != -1) {
    fassert(MS.count(task)==0, "Already submitted a machine for task=" + std::to_string(task));
    MS[task] = RULES;
  }

  ll score = 0;
  for(auto& kv : MS) {
    ll task; Cowputer M;
    std::tie(task, M) = kv;
    if(M.size() > 1000) {
      cerr << "You used more than 1000 internal states for task=" << task << endl;
      continue;
    }
    Checker check = TASKS[task];
    ll points = check(M, TRACE==task+1);
    score += points;
    cerr << "Task " << (task+1) << ": " << points << endl;
  }
  cout << score << endl;
}
