set<pair<double, int>> s;

s.insert({ 0, start });
distance[start] = 0;
distance[ sve ostalo ] = infinity;

while (!s.empty())
{
    double dist = s.front()->first;
    int node = s.front()->second;
    s.erase(s.front());
    
     for (int neighbor : neighbors[node])
     {
        double dist_to_neighbor = dist + (distance between node and neighbor);
        if (dist_to_neighbor >= distance[neighbor]) continue;
        
        s.erase({ distance[neighbor], neighbor });
        distance[neighbor] = dist_to_neighbor;
        s.insert({ distance[neighbor], neighbor });
     }
}
