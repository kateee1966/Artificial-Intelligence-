% tree(tree,root_value) return the root value of the tree. 
tree_value(tree(_, X, _), X). 
tree_value(empty, empty).

% is_heap(Tree) check if this tree satisfy the heap property.

is_heap(tree(empty, _, empty)).

is_heap(empty).

is_heap(tree(Left, Root, Right)) :-
		is_heap(Left),
		is_heap(Right),
		tree_value(Left, L),
		tree_value(Right, R),
		L \= empty,
		R \= empty,
		L >= Root,
		R >= Root.

		
is_heap(tree(Left, Root, Right)) :-
		is_heap(Left),
		is_heap(Right),
		tree_value(Left, L),
		tree_value(Right, R),
		L = empty,
		R \= empty,
		R >= Root.

is_heap(tree(Left, Root, Right)) :-
		is_heap(Left),
		is_heap(Right),
		tree_value(Left, L),
		tree_value(Right, R),
		L \= empty,
		L >= Root,
		R = empty.
		
		
		
		
		
		
		
		
		
		
		
		
		
sign_runs([],[]).

% judge neg and non_neg one by one and rid []
sign_runs([Head | Tail], RunList) :-
   judge_neg([Head | Tail], Left, Last_L_1),
   judge_nonneg(Last_L_1, Mid, Last_List_2),
   % here, 3 case as put the restlist the head as Mid /Left
   (Left = [] 
    -> Res = [Mid|Right]; % neg case
    Mid=[] 
    -> Res = [Left|Right]; % nonneg case
    Res=[Left,Mid|Right]),
   sign_runs(Last_List_2, Right).
% recursive to the end 


judge_neg([],[],[]). % Split even set

judge_neg([HE | TE], [], [HE | TE]) :-
   HE>=0.

judge_neg([HE | TE], [HE | LE], Final_List_E) :-
   HE<0,
   judge_neg(TE, LE, Final_List_E).

judge_nonneg([],[],[]). % Split odd set
judge_nonneg([HO | TO], [], [HO| TO]) :- 
   HO < 0.
judge_nonneg([HO | TO], [HO | IO], Final_List_O) :-
   HO>=0,
   judge_nonneg(TO, IO, Final_List_O).
   
   
   
   
   
   
   
   
   
   
   
   
   /*
sqrt_list(NumberList, ResultList) :-
    maplist(sq, NumberList, SqrttedList),
    pairing(NumberList,SqrttedList, ResultList).

% Terminating conditions for pairing empty lists
    pairing([], [Head|Tail], [Head|Tail]).
    pairing(Ls, [], Ls).

% Recursive step for pairing non-empty lists
    pairing([Head1|Tail1], [Head2|Tail2], [[Head1,Head2]|Tail]) :-
    pairing(Tail1, Tail2, Tail).

% evaluated using is to actually do the computation (i.e. sqr_t computes the square root)
sq(X,Y) :-
    Y is sqrt(X).
*/








sign_runs([],[]).

% judge neg and non_neg one by one and rid []
sign_runs([Head | Tail], Res) :-
   judge_neg([Head | Tail], Left, Last_L_1),
   judge_nonneg(Last_L_1, Mid, Last_List_2),
   % here, 3 case as put the restlist the head as Mid /Left
   (Left = [] 
    -> Res = [Mid|Right]; % neg case
    Mid=[] 
    -> Res = [Left|Right]; % nonneg case
    Res=[Left,Mid|Right]),
   sign_runs(Last_List_2, Right).
% recursive to the end 


judge_neg([],[],[]). % Split even set

judge_neg([HE | TE], [], [HE | TE]) :-
   HE>=0.

judge_neg([HE | TE], [HE | LE], Final_List_E) :-
   HE<0,
   judge_neg(TE, LE, Final_List_E).

judge_nonneg([],[],[]). % Split odd set
judge_nonneg([HO | TO], [], [HO| TO]) :- 
   HO < 0.
judge_nonneg([HO | TO], [HO | IO], Final_List_O) :-
   HO>=0,
   judge_nonneg(TO, IO, Final_List_O).
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   % empty case
sign_runs([],[]).

% one element case
sign_runs([E],[[E]]).

% judge neg and non_neg one by one and rid []
sign_runs([Head | Tail], RunList) :-
   judge_neg([Head | Tail], Left, Last_L_1),
   judge_nonneg(Last_L_1, Mid, Last_List_2),
   % here, 3 case as put the restlist the head as Mid /Left
   (Left = [] 
    -> RunList = [Mid|Right]; % neg case
    Mid=[] 
    -> RunList = [Left|Right]; % nonneg case
    RunList=[Left,Mid|Right]),
    
    sign_runs(Last_List_2, Right).
    % recursive to the end 


    

% Split neg set
judge_neg([],[],[]). 
judge_neg([H1 | T1], [], [H1 | T1]) :-
   H1>=0.
judge_neg([H1 | T1], [H1 | L1], Final_List_1) :-
   H1<0,
   judge_neg(T1, L1, Final_List_1).


% Split nonneg set
judge_nonneg([],[],[]). 
judge_nonneg([H2 | T2], [], [H2| T2]) :- 
   H2 < 0.
judge_nonneg([H2 | T2], [H2 | I2], Final_List_2) :-
   H2>=0,
   judge_nonneg(T2, L2, Final_List_2).
   
   
   
   % find_even([], []).
% To find all the even integers in given list
%
find_even([], []).
find_even([Head | Tail], Sum) :-
    not(0 is Head mod 2),
    !,
    find_even(Tail, Sum).
find_even([Head | Tail], [Head | Sum]) :-  
    find_even(Tail, Sum).

% sumsq([], 0).
% To sum all the squares of numbers in the given list
sumsq([], 0).
sumsq([Head | Tail], Sum) :-
    sumsq(Tail, Tail_Sum),
    Sum is Tail_Sum + Head*Head.

% To sum the squares of only the even numbers in a list of integers
sumsq_even(List, Sum) :-
    find_even(List, Liste),
    sumsq(Liste, Sum).
