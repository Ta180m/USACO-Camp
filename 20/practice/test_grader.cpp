#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>
#include <set>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <sstream>

#include <errno.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

#define L 1000000000000000LL

#define RETRY(x) ({                     \
  int _r = (x);                         \
  while (_r == -1 && errno == EINTR) {  \
    _r = (x);                           \
  }                                     \
  _r;                                   \
})

template<typename T>
string to_string(const T& x) {
  ostringstream sout;
  sout << x;
  return sout.str();
}

pid_t start_instance(int argc, char** argv, int* pipes) {
  int pipe_a[2];
  int pipe_b[2];
  if (pipe(pipe_a) == -1 || pipe(pipe_b) == -1) {
    perror("pipe");
    return -1;
  }

  pid_t pid = fork();
  if (pid == -1) {
    perror("fork");
    return -1;
  } else if (pid == 0) {
    close(0);
    close(1);
    dup2(pipe_b[0], 0);
    dup2(pipe_a[1], 1);
    close(pipe_a[0]);
    close(pipe_a[1]);
    close(pipe_b[0]);
    close(pipe_b[1]);

    char** args = (char**)malloc(sizeof(char*) * (argc + 2));
    args[0] = strdup("stdbuf");
    args[1] = strdup("-oL");
    for (int i = 1; i < argc; i++) {
      args[1 + i] = argv[i];
    }
    args[argc + 1] = NULL;
    execvp("stdbuf", args);
    perror("execvp");
    exit(1);
  }

  close(pipe_a[1]);
  close(pipe_b[0]);
  pipes[0] = pipe_a[0];
  pipes[1] = pipe_b[1];
  return pid;
}

int main(int argc, char** argv) {
  if (argc == 1) {
    cout << "USAGE:" << endl;
    cout << argv[0] << " ./test_program" << endl;
    return 0;
  }
  if (signal(SIGPIPE, SIG_IGN)) {
    perror("signal");
    return 1;
  }

  int nfds = 1;
  char buf[1024];
  int rfd[2];
  int wfd[2];
  pid_t pids[2];
  bool alive[2] = {true, true};
  bool returned[2] = {false, false};
  string return_val[2] = {"", ""};
  for (int i = 0; i < 2; i++) {
    int pipe_tmp[2];
    pids[i] = start_instance(argc, argv, pipe_tmp);
    if (pids[i] == -1) {
      cerr << "failed to start solution program" << endl;
      return 1;
    }

    rfd[i] = pipe_tmp[0];
    wfd[i] = pipe_tmp[1];
    nfds = max(nfds, max(rfd[i], wfd[i])) + 1;
  }

  int ign;
  vector<string > names[2];
  string in[2];
  string out[2];

  set<string> names_set[2];
  for (int i = 0; i < 2; i++) {
    int sz;
    cin >> ign >> sz;
    names[i].resize(sz);

    out[i] = to_string(i) + " " + to_string(sz) + "\n";
    for (int j = 0; j < sz; j++) {
      cin >> names[i][j];
      assert(0 <= names[i][j].size() && names[i][j].size() <= 100);
      for(int k = 0; k < names[i][j].size(); k++){
        assert('a' <= names[i][j][k] && names[i][j][k] <= 'z');
      }

      if (j) out[i] += ' ';
      out[i] += names[i][j];
    }
    out[i] += '\n';

    names_set[i] = set<string>(names[i].begin(), names[i].end());
    assert(names_set[i].size() == names[i].size());
  }
  vector<string> intersection;
  for(auto it = names_set[0].begin(); it != names_set[0].end(); ++it){
    if(names_set[1].count(*it)){
      cerr << "COMMON NAME: " << *it << endl;
      intersection.push_back(*it);
    }
  }
  assert(intersection.size() == 1);
  string answer_val = intersection[0];

  int total_bits = 0;
  for (; alive[0] || alive[1]; ) {
    fd_set rfds;
    fd_set wfds;
    FD_ZERO(&rfds);
    FD_ZERO(&wfds);
    for (int i = 0; i < 2; i++) {
      if (!alive[i]) {
        continue;
      }
      FD_SET(rfd[i], &rfds);
      if (out[i].size()) {
        FD_SET(wfd[i], &wfds);
      }
    }

    if (RETRY(select(nfds, &rfds, &wfds, NULL, NULL)) == -1) {
      perror("select");
      cout << "E" << endl;
      return 0;
    }

    for (int i = 0; i < 2; i++) {
      if (FD_ISSET(rfd[i], &rfds)) {
        ssize_t amt = RETRY(read(rfd[i], buf, sizeof(buf)));
        if (amt <= 0) {
          close(rfd[i]);
          close(wfd[i]);
          alive[i] = false;
          cerr << "Cow " << i << " communication closed" << endl;
          continue;
        }
        in[i] += string(buf, amt);
        cerr << "COW[" << i << "]: " << string(buf, amt) << endl;

        for(;;) {
          int nline = in[i].find('\n');
          if (nline == -1) {
            break;
          }
          string line = in[i].substr(0, nline);
          in[i] = in[i].substr(nline + 1);

          istringstream sin(line);
          string cmd; sin >> cmd;
          if (cmd == "MOO") {
            string data; sin >> data;
            for (int j = 0; j < data.size(); j++) {
              if (data[j] != '0' && data[j] != '1') {
                cerr << "Cow " << i << " tried to moo non-binary" << endl;
                return 1;
              }
            }
            out[1 - i] += data + "\n";
            total_bits += data.size();
          } else if (cmd == "RETURN") {
            string val;
            sin >> val;
            if (returned[i]) {
              cerr << "Same cow cannot return twice" << endl;
              return 1;
            } else {
              returned[i] = true;
              return_val[i] = val;
            }
          } else {
            cerr << "Unknown command from cow " << i << endl;
            return 1;
          }
        }
        if (in[i].size() > 7000000) {
          cerr << "Line too long from cow " << i << endl;
          return 1;
        }
      }
      if (FD_ISSET(wfd[i], &wfds)) {
        // cerr << "TO COW[" << i << "]: " << out[i] << endl;
        ssize_t amt = RETRY(write(wfd[i], out[i].data(), out[i].size()));
        if (amt <= 0) {
          close(rfd[i]);
          close(wfd[i]);
          alive[i] = false;
          cerr << "Cow " << i << " communication closed" << endl;
          continue;
        } else {
          out[i] = out[i].substr(amt);
        }
      }
    }
  }
  for (int i = 0; i < 2; i++) {
    int status = 0;
    if (RETRY(waitpid(pids[i], &status, 0)) == -1) {
      perror("waitpid");
      return 1;
    }
    if (WIFSIGNALED(status)) {
      cerr << "Cow " << i << " crashed" << endl;
      return 1;
    }
  }

  for (int i = 0; i < 2; i++) {
    if (returned[i] && return_val[i] != answer_val) {
      cerr << "Cow " << i << " returned the wrong value" << endl;
      return 1;
    }
  }
  if (!returned[0] && !returned[1]) {
    cerr << "Neither cow returned a value" << endl;
    return 1;
  }

  cerr << "Found correct name " << answer_val << " using " <<
          total_bits << " total bits." << endl;

  return 0;
}
