#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class LinearSATSolver {
public:
    LinearSATSolver(int numVariables) : numVariables(numVariables) {
        assignment.resize(numVariables, false);
    }

    void addClause(const vector<int>& clause) {
        clauses.push_back(clause);
    }
    bool solve() {
        for (const auto& clause : clauses) {
            bool clauseSatisfied = false;

            for (int literal : clause) {
                if (evaluateLiteral(literal)) {
                    clauseSatisfied = true;
                    break;
                }
            }

            if (!clauseSatisfied) {
                return false; // The formula is not satisfiable
            }
        }

        return true; // All clauses are satisfied
    }

    void printAssignment() const {
        cout << "Variable assignment: ";
        for (int i = 0; i < numVariables; ++i) {
            cout << "x" << i + 1 << "=" << (assignment[i] ? "true" : "false") << " ";
        }
        cout << endl;
    }

private:
    int numVariables;
    vector<vector<int>> clauses;
    vector<bool> assignment;

    bool evaluateLiteral(int literal) const {
        int variable = abs(literal) - 1;
        bool isNegated = (literal < 0);

        return (assignment[variable] ^ isNegated);
    }
};

int main() {
    LinearSATSolver solver(1);

    // Example clauses: (x1 OR x2) AND (NOT x1 OR x3) AND (x2 OR NOT x3)
    solver.addClause({-1, -2});
    //solver.addClause({3, 4});
    //solver.addClause({});

    if (solver.solve()) {
        cout << "Satisfiable!" << endl;
        solver.printAssignment();
    } else {
        cout << "Not satisfiable." << endl;
    }

    return 0;
}
/*/#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

bool isSatisfied(const std::vector<int>& clause, const std::unordered_map<int, bool>& assignment) {
for (int literal : clause) {
if (literal > 0 && assignment.count(literal) && assignment.at(literal)) {
return true;
} else if (literal < 0 && (!assignment.count(std::abs(literal)) || !assignment.at(std::abs(literal)))) {
return true;
}
}
return false;
}

std::unordered_map<int, bool>* satSolver(const std::vector<std::vector<int>>& clauses, std::unordered_map<int, bool> assignment = {}) {

// Check if all clauses are satisfied
bool allSatisfied = true; for (const auto& clause : clauses) {
if (!isSatisfied(clause, assignment)) {
allSatisfied = false;
break;
}
}
if (allSatisfied) {
return new std::unordered_map<int, bool>(assignment);
}

// Find unassigned variables
std::unordered_set<int> unassignedVars; for (const auto& clause : clauses) {
for (int literal : clause) {
if (!assignment.count(std::abs(literal))) {
unassignedVars.insert(std::abs(literal));
}
}
}
if (unassignedVars.empty()) {
return nullptr;
}

// Choose a variable to assign
int var = *unassignedVars.begin();

// Recursively try true and false assignments for the chosen variable
for (bool value : {true, false}) {
std::unordered_map<int, bool> newAssignment(assignment);
newAssignment[var] = value;
std::unordered_map<int, bool>* result = satSolver(clauses, newAssignment);
if (result != nullptr) { return result; } }

// No assignment found
return nullptr; }

int main() {
// Example usage:
std::vector<std::vector<int>> cnf = {{1, 2}, {3, 4}}; // The clauses of the CNF formula
std::unordered_map<int, bool>* solution = satSolver(cnf);
if (solution) {
std::cout << "SATISFIABLE with assignment:\n";
for (const auto& var : *solution) {
std::cout << "Variable " << var.first << " is " << (var.second ? "True" : "False") << std::endl;
}
delete solution;
} else {
std::cout << "UNSATISFIABLE" << std::endl;
}
return 0;
}
/*/
