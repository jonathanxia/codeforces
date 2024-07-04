#pragma once

#include <lib/common.h>

/**
 * Usage:
 * https://codesprintla24.kattis.com/contests/codesprintla24open/submissions/13660055
 * 
 * using namespace huffman;
 * // build a node
 * vector<double> freq = {0.1, 0.2, 0.3};
 * HuffmanTree tree(freq);
 * 
 * tree.depth[1]
*/
namespace huffman {
    // A Huffman tree node
    struct HuffmanNode {
        double freq;           // Frequency (probability) of the character
        HuffmanNode *left, *right; // Left and right child
        ll id; // An id number, only valid for leaf nodes

        HuffmanNode(double freq_, ll id_) {
            left = right = nullptr;
            this->freq = freq_;
            this->id = id_;
        }
        
        virtual ~HuffmanNode() {
            if (this->left != nullptr) {
                delete this->left;
                delete this->right;
            }
        }
    };

    // For comparison of two heap nodes (needed in min heap)
    struct compare {
        bool operator()(HuffmanNode* l, HuffmanNode* r) {
            return (l->freq > r->freq);
        }
    };

    // Function to build a Huffman Tree and return its root
    struct HuffmanTree {
        HuffmanNode * root;
        vl depth;

        HuffmanTree() {
            root = nullptr;
        }

        // exclude_zero: toss out zero frequency symbols from consideration
        HuffmanTree(const vector<double>& freq, bool exclude_zero=false) {
            ll n = len(freq);
            vl ids;
            vector<double> freq_;
            FOR(i, 0, n - 1) {
                if (!exclude_zero || freq[i] > 0) {
                    ids.pb(i);
                    freq_.pb(freq[i]);
                }
            }
            root = buildHuffmanTree(freq_, ids);
            depth.resize(n);
            computeDepths(root, 0);
        }

        HuffmanNode* buildHuffmanTree(const vector<double>& freq, const vl& ids) {
            priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> minHeap;
            walk(i, freq) {
                minHeap.push(new HuffmanNode(freq[i], ids[i]));
            }

            while (minHeap.size() != 1) {
                HuffmanNode* left = minHeap.top(); minHeap.pop();
                HuffmanNode* right = minHeap.top(); minHeap.pop();

                HuffmanNode* top = new HuffmanNode(left->freq + right->freq, -1);
                top->left = left;
                top->right = right;

                minHeap.push(top);
            }

            return minHeap.top();
        }

        void computeDepths(HuffmanNode * node, ll d) {
            if (node->left == nullptr) {
                assert(node->right == nullptr);
                depth[node->id] = d;
            }
            else {
                computeDepths(node->left, d + 1);
                computeDepths(node->right, d + 1);
            }
        }

        ~HuffmanTree() {
            delete root;
        }
    };
} // namespace huffman

