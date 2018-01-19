// feedforward.c
#include "feedforward.h"

void feedforward_once(LSTM_type *LSTM) {
  // Input preactivations:
  push(LSTM, At_iota, 
    sum(3, 
      product(2, 
        first(LSTM, Xt_i), 
        first(LSTM, Wi_iota)), 
      product(2, 
        second(LSTM, Bt_h), 
        first(LSTM, Wh_iota)), 
      product(2, 
        second(LSTM, St_c), 
        first(LSTM, Wc_iota))));

  // Input activations:
  push(LSTM, Bt_iota, matrix_sigmoid(first(LSTM, At_iota)));

  // Forget preactivations:
  push(LSTM, At_phi, 
    sum(3, 
      product(2, 
        first(LSTM, Xt_i), 
        first(LSTM, Wi_phi)), 
      product(2, 
        second(LSTM, Bt_h), 
        first(LSTM, Wh_phi)), 
      product(2, 
        second(LSTM, St_c), 
        first(LSTM, Wc_phi))));

  // Forget activations:
  push(LSTM, Bt_phi, matrix_sigmoid(first(LSTM, At_phi)));

  // Cell preactivations:
  push(LSTM, At_c, 
    sum(2, 
      product(2, 
        first(LSTM, Xt_i), 
        first(LSTM, Wi_c)), 
      product(2, 
        second(LSTM, Bt_h), 
        first(LSTM, Wh_c))));

  // Cell activations:
  push(LSTM, St_c, 
    sum(2, 
      product(2, 
        matrix_tanh(first(LSTM, At_c)), 
        first(LSTM, Bt_iota)), 
      product(2, 
        second(LSTM, St_c), 
        first(LSTM, Bt_phi))));

  // Output preactivations:
  push(LSTM, At_omega, 
    sum(3, 
      product(2, 
        first(LSTM, Xt_i), 
        first(LSTM, Wi_omega)), 
      product(2, 
        second(LSTM, Bt_h), 
        first(LSTM, Wh_omega)), 
      product(2, 
        first(LSTM, St_c), 
        first(LSTM, Wc_omega))));

  // Output activations:
  push(LSTM, Bt_omega, matrix_sigmoid(first(LSTM, At_omega)));

  // Cell outputs:
  push(LSTM, Bt_c, 
    product(2, 
      matrix_sigmoid(first(LSTM, St_c)), 
      first(LSTM, Bt_omega)));

}