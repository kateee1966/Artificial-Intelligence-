% Program:  mycode.pl
% Source:   Prolog
%
% Purpose:  This is the prolog work for assignment one in COMP3411.
%          
%
% History:  code by Wenfei Guo (z5135080) 18/3/2019

% Wenfei Guo (z5135080) Assignment_one completed 18/3/2019


% Question one
%

% sumsq_even(Numbers, Sum)
% To sum the squares of only the even numbers in a list of integers

% Examples of use:
% ?- sumsq_even([1,3,5,2,-4,6,8,-7], Sum).
% Sum = 120 

% if given list is empty
% return Sum = 0
sumsq_even([], 0).

% useing the built-in Prolog operator N mod M 
% to decide whether a number is even or odd

% if given list head is an odd number
sumsq_even([Head | Tail], Sum) :-
  sumsq_even(Tail, TailSum),
  Head mod 2 =:= 1,
  Sum is TailSum.

% if given list head is a even number
sumsq_even([Head | Tail], Sum) :-
  sumsq_even(Tail, TailSum),
  Head mod 2 =:= 0,
  Sum is (Head*Head)+TailSum.




 
    
% Question two
%
% same_name(Person1,Person2)
% To deduce from the facts in the database that Person1 and Person2 will have the same family name

% Example of uses in provided info:
% ?- same_name(pat, brian).
% false.
% ?- same_name(jenny, jim).
% true 

% Person1 is the father of Person2
same_name(Person1, Person2) :-
    parent(Person1, Person2),
    male(Person1),
    not(Person1 = Person2).

% Person2 is the father of Person1
same_name(Person1, Person2) :-
    parent(Person2, Person1),
    male(Person2),
    not(Person1 = Person2).

% Person1 and Person2 are siblings
% i.e Person1 and Person2 have the same father
same_name(Person1, Person2) :-
    parent(Parent, Person1),
    parent(Parent, Person2),
    male(Parent),
    not(Person1 = Person2).

% Person1 is the father of A, who
% is the father of Person2 
% i.e Person1 is the grandfather of Person2
same_name(Person1, Person2) :-
    parent(Person1, A),
    parent(A, Person2),
    male(Person1),
    male(A),
    not(Person1 = Person2).

% Person2 is the father of A, who
% is the father of Person1
% i.e Person2 is the grandfather of Person1
same_name(Person1, Person2) :-
    parent(Person2, A),
    parent(A, Person1),
    male(Person2),
    male(A),
    not(Person1 = Person2).
 
 
% Person1 and Person2 have a same common male ancestor.
same_name(Person1, Person2) :-
    male_ancestor(Person1, Ancestor),
    male_ancestor(Person2, Ancestor),
    male(Ancestor),
    not(Person1 = Person2).

% Person1 is a male ancestor of Person2
same_name(Person1, Person2) :-
    male_ancestor(Person2, Person1),
    male(Person1).

% Person2 is a male ancestor of Person1
same_name(Person1, Person2) :-
    male_ancestor(Person1, Person2),
    male(Person2).
    
% Person1 is a sibling of a male ancestor of Person2
same_name(Person1, Person2) :-
    siblings(Person1, Ancestor),
    male_ancestor(Person2, Ancestor),
    male(Ancestor).
    
% Person2 is a sibling of a male ancestor of Person1
same_name(Person1, Person2) :-
    siblings(Person2, Ancestor),
    male_ancestor(Person1, Ancestor),
    male(Ancestor).


% ancestor(Person, Ancestor)
% means Ancestor is an ancestor of Person.
male_ancestor(Person, Ancestor) :-
    male(Ancestor),
    parent(Ancestor, Person).        
male_ancestor(Person, Ancestor) :-
    male(Ancestor),
    parent(Parent, Person),
    ancestor(Parent, Ancestor). 

% siblings(Person1, Person2)
% means Person1 and Person2 are siblings
siblings(Person1, Person2) :-
    parent(X, Person1),       
    parent(X, Person2),
    Person1 \== Person2.


 
 
% Question three
%
% sqrt_list(NumberList, ResultList)
% To binds ResultList to the list of pairs consisting of a number and its square root, 
% for each number in NumberList

% Example of use:
% ?- sqrt_list([0,2,289], Result).
% Result = [[0, 0.0], [2, 1.4142135623730951], [289, 17.0]].

% if given list is empty
% return empty list
sqrt_list([], []).

% if givrn list is not empty
% Prolog built-in function sqr_t computes the square root, 
% and that it needs to be evaluated using is to actually do the computation
sqrt_list([Head | Tail], [[Head, Result_tail]|R]) :- 
    % using is to actually compute square root
    Result_tail is sqrt(Head), 
    sqrt_list(Tail, R). 
    
    
    
    
    
% Question four
%
% sign_runs(List, RunList)
% converts a list of numbers into the corresponding list of sign runs.
% each run is a (maximal) sequence of consecutive negative or non-negative numbers 
% within the original list.

% Example of use:
% ?- sign_runs([8,-1,-3,0,2,0,-4], RunList).
% RunList = [[8], [-1, -3], [0, 2, 0], [-4]]

% if given list is empty
% return empty list
sign_runs([],[]).

% if given list is not empty
sign_runs(List, RunList):-
 	find_neg(List,EL,OL),
 	find_nonneg(OL,OL1,EL1),
 	sign_runs(EL1,RList),
 	RunListTemp = [EL,OL1|RList],
 	delete(RunListTemp,[],RunList).
 	
% nonneg Predicates
nonneg(Num) :- 
	Num>=0.
% neg Predicate
neg(Num) :- 
	Num<0.

% Find the first neg prefix of a list.
% Base Cases
find_neg([],[],[]). 
find_neg([],_,_).

% Stop recursion if nonneg is found, 
% return empty accumulator and suffix incl head.
find_neg([H|T],[],[H|T]):-
	nonneg(H).
	
% If head of list is neg, 
% add to accumulator and recurse on tail
find_neg([H|T],[H|R],Suffix):-
	neg(H),
	find_neg(T,R,Suffix).



% Find the first nonneg prefix of a list.
% Base Cases
find_nonneg([],[],[]).
find_nonneg([],_,_).

% Stop recursion if neg is found, 
% return empty accumulator and suffix incl head.
find_nonneg([H|T],[],[H|T]):-
	neg(H).
	
% If head of list is nonneg, 
% add to accumulator and recurse on tail
find_nonneg([H|T],[H|R],Suffix):-
	nonneg(H),
	find_nonneg(T,R,Suffix).







% Question five
%

% Example of use:
% ?- is_heap(tree(tree(tree(empty,4,empty),
% 3,tree(empty,5,empty)),6,tree(tree(empty,9,empty),7,empty))).
% false.
% ?- is_heap(tree(empty,3,tree(tree(empty,8,empty),5,tree(empty,7,empty)))).
% true 

% rootv(tree(),root_value) 
% To get the input tree root value. 
rootv(tree(_, X, _), X). 
rootv(empty, empty).



% is_heap(Tree)
% To returns true if Tree satisfies the heap property, and false otherwise.

% base case
is_heap(tree(empty, _, empty)).
is_heap(empty).

is_heap(tree(L, Num, R)) :-
		is_heap(L),
		is_heap(R),
		rootv(L, L1),
		rootv(R, R1),
		L1 \= empty,
		R1 \= empty,
		L1 >= Num,
		R1 >= Num.

is_heap(tree(L, Num, R)) :-
		is_heap(L),
		is_heap(R),
		rootv(L, L1),
		rootv(R, R1),
		L1 = empty,
		R1 \= empty,
		R1 >= Num.

is_heap(tree(L, Num, R)) :-
		is_heap(L),
		is_heap(R),
		rootv(L, L1),
		rootv(R, R1),
		L1 \= empty,
		L1 >= Num,
		R1 = empty.

	
