#include "include.hpp"

KDNode* KDTree::build_kd_tree(std::vector<Point> &points, size_t depth){
    if(points.size() == 0){
        return nullptr;
    }

    size_t axis = depth % dimensions;
    size_t median = points.size() / 2;

    std::sort(points.begin(), points.end(), [axis](Point &a, Point &b){
        return a[axis] < b[axis];
    });

    KDNode *node = new KDNode(points[median]);
    std::vector<Point> left_points(points.begin(), points.begin() + median);
    std::vector<Point> right_points(points.begin() + median + 1, points.end());
    node->set_left(build_kd_tree(left_points, depth + 1));
    node->set_right(build_kd_tree(right_points, depth + 1));

    return node;
}

void KDTree::insert_node(Point point){
    KDNode *current = root;
    size_t depth = 0;

    while(true){
        size_t axis = depth % dimensions;

        if(point[axis] < current->get_point()[axis]){
            if(current->get_left() == nullptr){
                current->set_left(new KDNode(point));
                break;
            }else{
                current = current->get_left();
            }
        }
        else{
            if(current->get_right() == nullptr){
                current->set_right(new KDNode(point));
                break;
            }else{
                current = current->get_right();
            }
        }

        depth++;
    }
}

void KDTree::delete_node(Point point){
    KDNode *current = root;
    KDNode *parent = nullptr;
    size_t depth = 0;

    while(current != nullptr){
        size_t axis = depth % dimensions;

        if(current->get_point() == point){
            if(current->get_left() == nullptr && current->get_right() == nullptr){
                if(parent == nullptr){
                    root = nullptr;
                }else{
                    if(parent->get_left() == current){
                        parent->set_left(nullptr);
                    }else{
                        parent->set_right(nullptr);
                    }
                }
                delete current;
                break;
            }
            else{
                KDNode *successor = current->get_right();
                KDNode *successor_parent = current;

                while(successor->get_left() != nullptr){
                    successor_parent = successor;
                    successor = successor->get_left();
                }

                current->set_point(successor->get_point());
                if(successor_parent->get_left() == successor){
                    successor_parent->set_left(successor->get_right());
                }
                else{
                    successor_parent->set_right(successor->get_right());
                }
                delete successor;
                break;
            }
        }

        parent = current;
        if(point[axis] < current->get_point()[axis]){
            current = current->get_left();
        }
        else{
            current = current->get_right();
        }

        depth++;
    }
}