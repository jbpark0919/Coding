// 수식을 통한 최적화 (문제에 적혀있는 거 확인)
// 값의 범위가 정해져있으면 벡터를 생성하는 것보다 배열 생성이 빠름

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int arr[10];
int visited[10];
int n;
long long answer;
int total_sum;
int fact[10];

void backtrack(int depth, int left_sum, int right_sum) {
	if (left_sum >= right_sum + (total_sum - left_sum - right_sum)) {
		answer += fact[n - depth] * (1 << (n - depth));
		return;
	}

	if (depth == n) {
		answer++;
		return;
	}

	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			int now = arr[i];

			// 왼쪽에 두기
			visited[i] = 1;
			backtrack(depth + 1, left_sum + now, right_sum);
			visited[i] = 0;

			// 오른쪽에 두기
			if (right_sum + now <= left_sum) {
				visited[i] = 1;
				backtrack(depth + 1, left_sum, right_sum + now);
				visited[i] = 0;
			}
		}
	}
}

int main() {
	int T;
	cin >> T;

	fact[0] = 1;
	for (int i = 1; i < 10; i++) {
		fact[i] = fact[i - 1] * i;
	}

	for (int t = 0; t < T; t++) {
		cin >> n;

		answer = 0;
		total_sum = 0;
		
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
			total_sum += arr[i];
		}

		sort(arr, arr + n, greater<int>());

		backtrack(0, 0, 0);

		cout << "#" << t + 1 << ' ' << answer << "\n";
	}
}