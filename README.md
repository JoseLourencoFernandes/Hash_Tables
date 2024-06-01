<p align="center">
  <img w src="Hash_Tables.png">
</p>

# 1. Why this project?
This project was developed in the context of <em>Laboratórios de Informática II</em> discipline taught on Informatics Engineering in University of Minho, Portugal. This project has the objective to acquire and understood as different data types react and work based on hashing.

# 2. Guideline for the project

## Objective
Your goal is to simulate three kinds of conflict resolutions for Hash tables:

- Open addressing with linear probing and lazy removal
- Linked lists
- Cuckoo hashing

## Language
We are going to use a language for out table:

- I number if the number does not exist adds the number to the table and prints OK otherwise prints number EXISTS
- D number deletes the number from the table if it exists and prints OK, prints NO otherwise
- C number checks if the number is on the table and prints the location, prints NO if the number is not on the table
- P prints the table omiting empty slots

## Adding keys

When adding a key:

- you use the hash function to select the position of the array where you will add the key<
- if the position is free, we add the key otherwise, we go to the confict resolution phase!

## Conflict resolution

### Linear probing
- start searching for the first free position after the slot corresponding to $h(x)$, wrapping around if necessary;
- add the key to that position;
- if there are no free positions, fail!
- in this method we use lazy removal: we only mark the cell for removal;
- if we search for a value $x$:
    - we start at $h(x)$ and:
    - we keep going down until we find the key, wrapping around if necessary;
    - if during this process we find a deleted cell, we store the position of the first deleted cell we find;
    - if we find the key we move it to the first deleted cell we found when searching for it.
    - we use this process both for inserting and searching for a key,

### Linked lists

- add the current key to the head of the linked list
- the linked list needs to be traversed for removals or search

### Cuckoo hashing

- Use two tables $t_{1}$ and $t_{2}$ of the same size and two hash functions and two hash functions $h_{1}$ and $h_{2}$
- Try to insert key $x$ in table $t_{1}$ at slot $h_{1}(x)$
- If the slot is occupied:
    - 1. Recursively add the current key in slot $h_{1}(x)$ of table $t_{1}$, $y$, to the other table (e.g., $t_{2}$ using hash function $h_{2}(x)$)
    - 2. Add $x$ to table $t_{1}$ at slot $h_{1}(x)$
- It should give up after P (table size) tries.
- When searching for key $x$ , search it in both $t_{1}$ and $t_{1}$ using $h_{1}(x)$ and $h_{2}(x)$

## Implementation

We are going to use as hash functions:<br>

$h_{1}(x)$ $=$ $x$ $mod$ $P$<br>
$h_{2}(x)$ $=$ $floor(\frac{x}{P})$ $mod$ $P$

where $x$ and $P$ are integers.

## Constraints

- All numbers inserted in the table are non negative and fit into an integer

## Input

The input has the following lines:

- The first line has the number of slots;
- The second line is one of the words OPEN, LINK or CUCKOO;
- Each of the following lines is one of the following:
    - <strong>I</strong> number insert the number if it doesn’t exist;
    - <strong>D</strong> number delete the number if it exists;
    - <strong>C</strong> number consult the number if it exists;
    - <strong>P</strong> Print the data structure, it doesn’t print anything if the structure is empty.

## Output

The output should be one line per command and depends on the kind of conflict resolution.

### Open
I

- If the key already exists, print key EXISTS
- If the key was added, print the index then the key sepparated by ->
- If it was impossible to add the key, print GIVING UP!

C

- If the key exists, print the index
- Otherwise print NO

D

- If the key exists, delete it and print OK
- Otherwise print NO

P

For each occupied slot print the slot, a tab and the key

### Link
I

- If the key already exists, print key EXISTS
- If the key was added, print the index then the key sepparated by ->

C

- If the key exists, print the index
- Otherwise print NO

D

- If the key exists, delete it and print OK
- Otherwise print NO

P

For each occupied slot print the slot and each of the keys sepparated by spaces. The keys should be printed assuming they were inserted at the head of the list.

### Cuckoo
I

- If the key already existed, print key EXISTS
- If the key was added, print the table index, a tab, followed by the index then -> and the key
- If several relocations happened, print them as you are working through each one using the same notation as above
- If it was impossible to add the key, print GIVING UP!!!

C

- If the key exists, print the table index followed by a tab and index
- Otherwise print NO

D

- If the key exists, delete it and print OK
- Otherwise print NO

P

For each occupied slot print the table slot, a tab, the slot, a tab and the key. Order by table index then slot indexes.

## Examples 

All example outputs include >>> and the command that originated the output. This is not present in the output! It is just here to clarify.

### Example 1

Input

    11
    CUCKOO
    I 11
    I 22
    I 33
    I 44
    I 154
    I 1694
    P

Output


    >>> I 11
    0 0 -> 11
    OK
    >>> I 22
    0 0 -> 22
    1 1 -> 11
    OK
    >>> I 33
    0 0 -> 33
    1 2 -> 22
    OK
    >>> I 44
    0 0 -> 44
    1 3 -> 33
    OK
    >>> I 154
    0 0 -> 154
    1 4 -> 44
    OK
    >>> I 1694
    0 0 -> 1694
    1 3 -> 154
    0 0 -> 33
    1 0 -> 1694
    OK
    >>> P
    0   0   33
    1   0   1694
    1   1   11
    1   2   22
    1   3   154
    1   4   44

### Example 2

Input

    5
    CUCKOO
    I 6
    I 1
    I 11
    I 16
    I 21
    I 26
    P
    I 31

Output

    >>> I 6
    0 1 -> 6
    OK
    >>> I 1
    0 1 -> 1
    1 1 -> 6
    OK
    >>> I 11
    0 1 -> 11
    1 0 -> 1
    OK
    >>> I 16
    0 1 -> 16
    1 2 -> 11
    OK
    >>> I 21
    0 1 -> 21
    1 3 -> 16
    OK
    >>> I 26
    0 1 -> 26
    1 4 -> 21
    OK
    >>> P
    0   1   26
    1   0   1
    1   1   6
    1   2   11
    1   3   16
    1   4   21
    >>> I 31
    0 1 -> 31
    1 0 -> 26
    0 1 -> 1
    1 1 -> 31
    0 1 -> 6
    1 0 -> 1
    GIVING UP!

### Example 3

Input

    11
    LINK
    I 21
    I 10
    I 11
    P
    I 43
    P
    D 10
    P
    C 43

Output

    >>> I 21
    10 -> 21
    OK
    >>> I 10
    10 -> 10
    OK
    >>> I 11
    0 -> 11
    OK
    >>> P
    0 11
    10 10 21
    >>> I 43
    10 -> 43
    OK
    >>> P
    0 11
    10 43 10 21
    >>> D 10
    OK
    >>> P
    0 11
    10 43 21
    >>> C 43
    10

### Example 4

Input

    5
    OPEN
    I 12
    I 15
    I 21
    I 6
    P
    D 21
    P
    I 6
    P
    I 23
    I 30
    P
    D 23
    D 6
    P
    C 30
P

Output

    >>> I 12
    2 -> 12
    OK
    >>> I 15
    0 -> 15
    OK
    >>> I 21
    1 -> 21
    OK
    >>> I 6
    3 -> 6
    OK
    >>> P
    0   15
    1   21
    2   12
    3   6
    >>> D 21
    OK
    >>> P
    0   15
    1   D
    2   12
    3   6
    >>> I 6
    6 EXISTS
    >>> P
    0   15
    1   6
    2   12
    3   D
    >>> I 23
    3 -> 23
    OK
    >>> I 30
    4 -> 30
    OK
    >>> P
    0   15
    1   6
    2   12
    3   23
    4   30
    >>> D 23
    OK
    >>> D 6
    OK
    >>> P
    0   15
    1   D
    2   12
    3   D
    4   30
    >>> C 30
    1
    >>> P
    0   15
    1   30
    2   12
    3   D
    4   D

# 3. Executing the code
Compile the "main.c" file and use it based on the required inputs explained on 2.
