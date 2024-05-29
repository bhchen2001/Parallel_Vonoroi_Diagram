#include <KDTree.hpp>

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
    node->left = build_kd_tree(std::vector<Point>(points.begin(), points.begin() + median), depth + 1);
    node->right = build_kd_tree(std::vector<Point>(points.begin() + median + 1, points.end()), depth + 1);

    return node;
}

void KDTree::insert_node(Point point){
    KDNode *current = root;
    size_t depth = 0;

    while(true){
        size_t axis = depth % dimensions;

        if(point[axis] < current->point[axis]){
            if(current->left == nullptr){
                current->left = new KDNode(point);
                break;
            }else{
                current = current->left;
            }
        }else{
            if(current->right == nullptr){
                current->right = new KDNode(point);
                break;
            }else{
                current = current->right;
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

        if(current->point == point){
            if(current->right != nullptr){
                KDNode *min = current->right;
                KDNode *min_parent = current;

                while(min->left != nullptr){
                    min_parent = min;
                    min = min->left;
                }

                current->point = min->point;
                current = min;
                parent = min_parent;
            }else if(current->left != nullptr){
                KDNode *max = current->left;
                KDNode *max_parent = current;

                while(max->right != nullptr){
                    max_parent = max;
                    max = max->right;
                }

                current->point = max->point;
                current = max;
                parent = max_parent;
            }else{
                if(parent == nullptr){
                    root = nullptr;
                }else{
                    if(parent->left == current){
                        parent->left = nullptr;
                    }else{
                        parent->right = nullptr;
                    }
                }

                delete current;
                break;
            }
        }else if(point[axis] < current->point[axis]){
            parent = current;
            current = current->left;
        }else{
            parent = current;
            current = current->right;
        }

        depth++;
    }
}