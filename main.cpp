#include <bits/stdc++.h>

using namespace std;

struct cache_connection {
    int cache_id;
    int latency;
};

struct request {
    int video_id;
    int endpoint_id;
    int count;
};

int v, e, r, c, x;
vector<int> video_sizes;
vector<int> latency_to_dc;
vector<vector<cache_connection>> endpoint_caches;
vector<request> requests;

struct solution {
    vector<unordered_set<int>> cached_videos;
    long long score;

    // Score is calculated in constructor.
    solution(const vector<unordered_set<int>>& cached_videos) : cached_videos(cached_videos) {
        long long saved_time = 0;
        long long total_request_count = 0;

        for (const request& r: requests) {
            int minimum_latency = latency_to_dc[r.endpoint_id];

            for (const cache_connection& cc: endpoint_caches[r.endpoint_id]) {
                if (cached_videos[cc.cache_id].find(r.video_id) != cached_videos[cc.cache_id].end()) {
                    minimum_latency = min(minimum_latency, cc.latency);
                }
            }

            saved_time += r.count * (latency_to_dc[r.endpoint_id] - minimum_latency);
            total_request_count += r.count;
        }

        saved_time *= 1000;
        saved_time /= total_request_count;

        score = saved_time;
    }
};

int main() {
    cin >> v >> e >> r >> c >> x;

    video_sizes.resize(v);

    for (int i = 0; i < v; i++) {
        cin >> video_sizes[i];
    }

    latency_to_dc.resize(e);
    endpoint_caches.resize(e);

    for (int i = 0; i < e; i++) {
        int k;
        cin >> latency_to_dc[i] >> k;

        endpoint_caches[i].resize(k);

        for (int j = 0; j < k; j++) {
            cin >> endpoint_caches[i][j].cache_id >> endpoint_caches[i][j].latency;
        }
    }

    requests.resize(r);

    for (int i = 0; i < r; i++) {
        cin >> requests[i].video_id >> requests[i].endpoint_id >> requests[i].count;
    }

    // Debug:
    
    unordered_set<int> a, b, c;
    a.insert(2);
    b.insert(3); b.insert(1);
    c.insert(0); c.insert(1);

    vector<unordered_set<int>> v;
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);

    solution s(v);

    cout << s.score << endl;
}
