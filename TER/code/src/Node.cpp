#include "Node.h"

Node::Node(){
	m_walkable = true;
	m_g = m_h = m_f = 0;
	m_parent = this;
}

Node::~Node(){

}

bool Node::estEgal(Node const& b) const
{
    return (m_X == b.m_X && m_Y == b.m_Y && m_f == b.m_f && m_g == b.m_g &&
    		m_h == b.m_h && m_walkable == b.m_walkable && m_parent == b.m_parent);
}


void Node::setParent(Node* val){m_parent = val;}
Node* Node::getParent(){return m_parent;}
