/** Node of pointers for a linked list
  *
  * @author Richard Szeto
  *
  *
  *
  */

package com.RichardSzeto.checkers.NotActivities;

public class Node<T>
{
    protected T data;
    protected Node<T> link;
    
    public Node()
    {
        data = null;
        
        link = null;
        
    }
    
    public Node(T newData)
    {
        data = newData;
        
        link = null;
    }
    
    public Node(T newData, Node<T> newLink)
    {
        data = newData;
        
        link = newLink;
    }
    
    public Node(final Node<T> node)
    {
        data = node.data;
        
        link = node.link;
    }
   
    public void clear()
    {
        data = null;
        
        link = null;
    }
    
    public T getData()
    {
        return data;
    }
    
    public Node<T> getLink()
    {
        return link;
    }
    
    public void setData(T newData)
    {
        data = newData;
    }
    
    public void setLink(Node<T> newLink)
    {
        link = newLink;
    }
}