//
// Created by Mykhailo_Shamrai on 12.05.2025.
//

#ifndef ALG_NODE_H
#define ALG_NODE_H

#include <memory>
#include "board.h"

struct AlgNode
{
    AlgNode(const std::shared_ptr<AlgNode>& parent, const Board& board, double priority, const Move& move):
                     parent(parent), board(board), priority(priority), move(move) {};
    std::shared_ptr<AlgNode> parent;
    Board board;
    double priority;
    Move move;
};

struct AlgNodeComparator
{
    bool operator()(const std::shared_ptr<AlgNode>& lhs, const std::shared_ptr<AlgNode>& rhs) const
    {return std::isless(lhs->priority, rhs->priority);}
};

#endif //ALG_NODE_H
