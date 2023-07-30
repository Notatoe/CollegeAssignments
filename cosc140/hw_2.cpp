// Noah Morris
// 9/3/2020
// cosc140
// Homework 2


void push_front(const int& din)
{
	node *temp = new node(din);

	p->next = head->next;
	head->next = temp;

	N++;
}
void pop_front()
{
	node *temp;

	temp = head->next;
	head->next = temp->next;
	delete temp;

	N--;

}
const int &front()
{
	node *temp

		temp = head->next;

	return temp->data;
}


