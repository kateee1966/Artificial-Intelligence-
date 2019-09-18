% Author: Rachael Ruixi Yu
% Student ID: z5164297
% Assignment: Prolog Programming

% sumsq_even(Numbers, Sum)
% This predicate sums the squares of only the even numbers in a list of integers

    % generate an EvenList containinng all even numbers from [H|T]
    even([], []).

    even([H|T], EvenList) :-
        number(H),
        1 is H mod 2,
        even(T, EvenList).

    even([H|T], [H|EvenList]) :-
        number(H),
        0 is H mod 2,
        even(T, EvenList).

    % calculate the sum of the square of all numbers in the new list after removing odd numbers
    sumsq_even([], 0).

    sumsq_even(Numbers, Sum) :-
        even(Numbers, [H|T]),
        sumsq_even(T, SumT),
        Sum is H * H + SumT.

% same_name(Person1,Person2)
% This predicate checks if Person1 and Person2 have the same family name

    % check if Person1 and Person2 are siblings
    siblings(Person1, Person2) :-
        parent(Parent, Person1),
        parent(Parent, Person2),
        male(Parent),
        Person1 \== Person2.

    % check if Ancestor is a male ancestor of Person
    ancestor(Person, Ancestor) :-
        parent(Ancestor, Person),
        male(Ancestor).
    ancestor(Person, Ancestor) :-
        parent(Parent, Person),
        ancestor(Parent, Ancestor).

    % check if Person1 and Person2 are siblings
    same_name(Person1, Person2) :-
        siblings(Person1, Person2).

    % check if Person1 is a male ancestor of Person2
    same_name(Person1, Person2) :-
        ancestor(Person2, Person1).

    % check if Person2 is a male ancestor of Person2
    same_name(Person1, Person2) :-
        ancestor(Person1, Person2).

    % check if Person1 and Person2 have a common male ancestor
    same_name(Person1, Person2) :-
        ancestor(Person1, X),
        ancestor(Person2, X).

    % check if Person1 is a sibling of a male ancestor of Person2
    same_name(Person1, Person2) :-
        siblings(Person1, Ancestor),
        ancestor(Person2, Ancestor).

    % check if Person2 is a sibling of a male ancestor of Person1
    same_name(Person1, Person2) :-
        siblings(Person2, Ancestor),
        ancestor(Person1, Ancestor).

% sqrt_list(NumberList, ResultList)
% This predicate binds ResultList to the list of pairs consisting of numbers from NumberList and its root

    sqrt_list([], []).

    sqrt_list([H|T], [[H,R]|Result]) :-
        number(H),
        H >= 0,
        R is sqrt(H),
        sqrt_list(T, Result).

% sign_runs(List, RunList)
% This predicate converts a list of numbers into a list consisting of sign runs that are lists of consecutive numbers with the same sign

    sign_runs([], []).

    sign_runs([H], [[H]]) :-
        number(H).

    sign_runs([H|T], RunList) :-
        number(H),
        sign_runs(T, [[X|T2]|L]),
        0 =< H,
        0 =< X,
        RunList = [[H, X|T2]|L].

    sign_runs([H|T], RunList) :-
        number(H),
        sign_runs(T, [[X|T2]|L]),
        0 > H,
        0 > X,
        RunList = [[H, X|T2]|L].

    sign_runs([H|T], RunList) :-
        number(H),
        sign_runs(T, [[X|T2]|L]),
        0 =< H,
        0 > X,
        RunList = [[H], [X|T2]|L].

    sign_runs([H|T], RunList) :-
        number(H),
        sign_runs(T, [[X|T2]|L]),
        0 > H,
        0 =< X,
        RunList = [[H], [X|T2]|L].

% is_heap(Tree)
% This predicate returns true if for every non-leaf node in Tree, the number stored at that node is less than or equal to the number stored at each of its children

    % check if a given value is smaller or equal to the root value of the tree
    lower(X, tree(_, N, _)) :-
        X =< N.

    is_heap(tree(L, N, R)) :-
        number(N),
        is_heap(L),
        is_heap(R),
        L \= empty,
        R \= empty,
        lower(N, L),
        lower(N, R).

    is_heap(N) :-
        N = empty.

    is_heap(tree(L, N, R)) :-
        number(N),
        R = empty,
        is_heap(L),
        L \= empty,
        lower(N, L).

    is_heap(tree(L, N, R)) :-
        number(N),
        L = empty,
        is_heap(R),
        R \= empty,
        lower(N, R).

    is_heap(tree(L, N, R)) :-
        number(N),
        R = empty,
        L = empty.
