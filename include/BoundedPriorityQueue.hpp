#include "Point.hpp"

#include <queue>

struct PairComparator{
    bool operator()(const std::pair<double, Point> &p1, const std::pair<double, Point> &p2){
        return p1.first < p2.first;
    }
};

class BoundedPriorityQueue{
    private:
        std::vector<std::pair<double, Point>> pq;
        size_t capacity = 0;

    public:
        /*
         * Constructor
         */
        
        BoundedPriorityQueue(size_t capacity){
            this->capacity = capacity;
        }

        /*
         * Getter
         */

        size_t get_capacity(){
            return capacity;
        }

        size_t get_size(){
            return pq.size();
        }

        double max_priority(){
            return pq.front().first;
        }

        std::vector<Point> get_points(){
            std::vector<Point> points;
            for(auto const &pair : pq){
                points.push_back(pair.second);
            }
            return points;
        }

        /*
         * Operations
         */

        void push(double distance, Point const &point){
            if(pq.size() < capacity){
                pq.push_back(std::make_pair(distance, point));
                std::push_heap(pq.begin(), pq.end(), PairComparator());
            }
            else{
                if(distance < pq.front().first){
                    std::pop_heap(pq.begin(), pq.end(), PairComparator());
                    pq.pop_back();
                    pq.push_back(std::make_pair(distance, point));
                    std::push_heap(pq.begin(), pq.end(), PairComparator());
                }
            }
        }
};