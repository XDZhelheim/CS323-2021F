/*
Non-terminals: S, T, E, F, X
Terminal: a, +, *, (, )
S -> TE
E -> +TE
E -> ε
T -> FX
X -> *FX
X -> ε
F -> (S)
F -> a
*/

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Stack;
import java.util.Queue;

public class Parser {
    static ArrayList<Character> nonterminals = new ArrayList<>();
    static ArrayList<Character> terminals = new ArrayList<>();
    static ArrayList<Production> productions = new ArrayList<>();
    static Production[][] parsingTable;
    static {
        populateParsingTable();
    }
    static Queue<Character> inputBuffer;
    static ArrayList<Production> productionsToApply;

    public static void main(String[] args) throws Exception {
        if (args == null || args.length == 0)
            return;

        try {
            System.out.println("Recursion:");
            initInputBuffer(args[0]);
            recursionParse();
        } catch (Exception e) {
            System.out.println("error");
        }

        System.out.println();

        try {
            System.out.println("Iteration:");
            initInputBuffer(args[0]);
            iterationParse();
        } catch (Exception e) {
            System.out.println("error");
        }
    }

    public static void initInputBuffer(String arg) {
        inputBuffer = new LinkedList<>();
        for (char c : arg.toCharArray()) {
            inputBuffer.offer(c);
        }
        inputBuffer.offer('$');
    }

    public static void iterationParse() throws Exception {
        productionsToApply = new ArrayList<>();
        Stack<Character> stack = new Stack<>();
        stack.push('$');
        stack.push('S');

        char a = inputBuffer.peek();
        char X = stack.peek();
        while (X != '$') {
            if (X == a) {
                stack.pop();
                inputBuffer.poll();
                a = inputBuffer.peek();
            } else if (terminals.contains(X) || parsingTable[nonterminals.indexOf(X)][terminals.indexOf(a)] == null) {
                throw new Exception("error");
            } else {
                Production prod = parsingTable[nonterminals.indexOf(X)][terminals.indexOf(a)];
                productionsToApply.add(prod);
                stack.pop();
                for (int i = prod.body.size() - 1; i >= 0; i--) {
                    stack.push(prod.body.get(i));
                }
            }
            X = stack.peek();
        }
        for (Production p : productionsToApply)
            p.print();
        System.out.println("success");
    }

    public static void recursionParse() throws Exception {
        productionsToApply = new ArrayList<>();

        procedure('S');

        if (inputBuffer.size() == 1 && inputBuffer.peek().charValue() == '$') {
            for (Production p : productionsToApply)
                p.print();
            System.out.println("success");
        }
    }

    public static void procedure(Character nonterminal) throws Exception {
        if (terminals.indexOf(inputBuffer.peek()) == -1) {
            throw new Exception("error");
        }
        Production prod = parsingTable[nonterminals.indexOf(nonterminal)][terminals.indexOf(inputBuffer.peek())];
        productionsToApply.add(prod);
        for (Character x : prod.body) {
            if (nonterminals.contains(x)) {
                procedure(x);
            } else if (x.equals(inputBuffer.peek())) {
                inputBuffer.poll();
            } else {
                throw new Exception("error");
            }
        }
    }

    public static void populateParsingTable() {
        // create non-terminals
        nonterminals.add('S');
        nonterminals.add('T');
        nonterminals.add('E');
        nonterminals.add('F');
        nonterminals.add('X');

        // create terminals
        terminals.add('a');
        terminals.add('+');
        terminals.add('*');
        terminals.add('(');
        terminals.add(')');
        terminals.add('$');

        // add entries to parsing table
        parsingTable = new Production[nonterminals.size()][terminals.size()];
        Production p1 = new Production('S', 'T', 'E');
        parsingTable[nonterminals.indexOf('S')][terminals.indexOf('a')] = p1;
        parsingTable[nonterminals.indexOf('S')][terminals.indexOf('(')] = p1;
        parsingTable[nonterminals.indexOf('E')][terminals.indexOf('+')] = new Production('E', '+', 'T', 'E');
        Production p2 = new Production('E', new Character[] {});
        parsingTable[nonterminals.indexOf('E')][terminals.indexOf(')')] = p2;
        parsingTable[nonterminals.indexOf('E')][terminals.indexOf('$')] = p2;
        Production p3 = new Production('T', 'F', 'X');
        parsingTable[nonterminals.indexOf('T')][terminals.indexOf('a')] = p3;
        parsingTable[nonterminals.indexOf('T')][terminals.indexOf('(')] = p3;
        Production p4 = new Production('X', new Character[] {});
        parsingTable[nonterminals.indexOf('X')][terminals.indexOf('+')] = p4;
        parsingTable[nonterminals.indexOf('X')][terminals.indexOf('*')] = new Production('X', '*', 'F', 'X');
        parsingTable[nonterminals.indexOf('X')][terminals.indexOf(')')] = p4;
        parsingTable[nonterminals.indexOf('X')][terminals.indexOf('$')] = p4;
        parsingTable[nonterminals.indexOf('F')][terminals.indexOf('a')] = new Production('F', 'a');
        parsingTable[nonterminals.indexOf('F')][terminals.indexOf('(')] = new Production('F', '(', 'S', ')');
    }
}

class Production {
    Character head;
    ArrayList<Character> body;

    public Production(Character head, Character... body) {
        this.head = head;
        this.body = new ArrayList<Character>(Arrays.asList(body));
    }

    public void print() {
        System.out.print(head);
        System.out.print("->");
        if (body.size() == 0) {
            System.out.println("\u03B5");
            return;
        }
        for (Character c : body) {
            System.out.print(c);
        }
        System.out.println();
    }
}
