//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Andrej Pavlovič <xpavlo14@stud.fit.vutbr.cz>
// $Date:       $2022-03-01
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Andrej Pavlovič
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

PriorityQueue::PriorityQueue()
{
    this->m_pHead = nullptr;
}

PriorityQueue::~PriorityQueue()
{
    // Dealloc elements
    if (this->m_pHead) {
        Element_t *pLast, *pNext = this->m_pHead;

        do {
            pLast = pNext;
            pNext = pNext->pNext;
            free(pLast);
        } while (pNext);
    }
}

void PriorityQueue::Insert(int value)
{
    if ((!this->m_pHead) || value >= this->m_pHead->value) {
        Element_t* newElement = (Element_t*) malloc(sizeof(Element_t));
        newElement->pNext = this->m_pHead;
        newElement->value = value;
        this->m_pHead = newElement;
    } else {
        Element_t *pLast, *pNext = this->m_pHead;

        while ((pLast = pNext, pNext = pNext->pNext)) {
            if (value >= pNext->value) {
                break;
            }
        }

        pLast->pNext = (Element_t*) malloc(sizeof(Element_t));
        pLast->pNext->pNext = pNext;
        pLast->pNext->value = value;
    }
}

bool PriorityQueue::Remove(int value)
{
    // Queue is empty
    if (this->m_pHead == nullptr) {
        return false;
    }

    Element_t *pNext = this->m_pHead, *pLast;

    // Element to delete is head
    if (pNext->value == value) {
        this->m_pHead = pNext->pNext;
        free(pNext);
        return true;
    }

    // Element to delete is not head
    while (pLast = pNext, pNext = pNext->pNext) {
        if (pNext->value == value) {
            pLast->pNext = pNext->pNext;
            free(pNext);
            return true;
        }
    }

    // Element to delete does not exist
    return false;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    Element_t* pNext = this->m_pHead;

    while (pNext) {
        if (pNext->value == value) {
            return pNext;
        }

        pNext = pNext->pNext;
    }

    return nullptr;
}

size_t PriorityQueue::Length()
{
    size_t size = 0;
    Element_t* pNext = this->m_pHead;

    while (pNext) {
        size++;
        pNext = pNext->pNext;
    }

    return size;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return this->m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
