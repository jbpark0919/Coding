// 문자열 입력
// 문자열 자르기
// 정렬
// 중복 제거

// 내림차순 정렬
// 중복 제거 필수

// 값 범위를 통해 FFF FFFF가 int 범위 내인지 확인

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
	int T;
	cin >> T;

	for (int t = 0; t < T; t++) {
		int N, K;
		cin >> N >> K;

        string str;
        cin >> str;
        str += str;

		vector<string> v;
		for (int i = 0; i < N; i++) {
			string sub = str.substr(i, N / 4);
			v.push_back(sub);
		}

		// 내림 차순
		sort(v.begin(), v.end(), greater<string>());

		// 중복 제거
		vector<string> v_set;
		v_set.push_back(v[0]);

		for (int i = 1; i < v.size(); i++) {
			if (v[i - 1] != v[i]) v_set.push_back(v[i]);
		}

		// for (string s : v_set) cout << s << ' ';

		int answer = stoi(v_set[K - 1], NULL, 16);
		cout << "#" << t + 1 << ' ' << answer << "\n";
	}

	return 0;
}