#include "transpilers.h"




// QuantumCircuit simplification(const QuantumCircuit& qc){
//     QuantumCircuit new_qc;
//     int size=0;

//     for(auto x : qc){
//         auto qubits = x->qubits;
//         equal_qubits = bool(pred[qubits[0]]) && (pred[qubits[0]]->qubits.size() == qubits.size());
//         if (equal_qubits){
//             for (int i=0; i < qubits.size(); i++){
//                 if (qubits[i] != (pred[qubits[0]] -> qubits)[i]){
//                     equal_qubits = false;
//                     break;
//                 }
//             }
//             if (qubits.size() == 2 && (pred[qubits[0]] -> qubits).size() == 2){
//                 if (qubits[0] == (pred[qubits[0]] -> qubits)[1] && qubits[1] == (pred[qubits[0]] -> qubits)[0]){
//                     std::cout << x->un << std::endl;
//                     std::cout << x->qubits[0] << std::endl;
//                     x->reverse_qubits(IntArr{1,0});
//                     std::cout << x->un << std::endl;
//                     std::cout << x->qubits[0] << std::endl;
//                     qubits = x->qubits;
//                     equal_qubits == true;
//                 }
//             }
//             if (equal_qubits){
//                 pred[qubits[0]]->un = (x->un) * (pred[qubits[0]]->un) ;
//                 auto old = x;
//                 x--;
//                 qc_data.erase(old);
//             } 
//         }
//         if (!equal_qubits){
//             for (auto q: qubits){
//                 if (pred[q]){
//                     for (auto qpred: pred[q]->qubits){
//                         pred[qpred] = nullptr;
//                     }
//                 }
//             }
//             for (auto q: qubits){
//                 pred[q] = &(*x);
//             }
//         }

//     }
// };