# Todo
This repository hosts a suite of note taking tools implemented in different programming lanugages, written mainly to serve as a step up from generic "hello world" projects which must be able to at least perform the following tasks:

- Enqueue a note
- List all notes
- Dequeue a particular note from the queue

## Usage
Invoking `todo`, without any arguements, returns the last note added to the queue.

Enqueueing a note is done using the following syntax:
```
Todo -a "This is a note."
``` 

Printing a numbered list of notes added to the program, with the most recent note added the last, is done as such:
```
Todo -l
```

Removing an item from the list can be done by invoking:
```
Todo -d <number>
```
Where `<number>` is a natural integer which defaults to 1 (aka the first note which was added)

Any other combination of command line arguements will display an help page
