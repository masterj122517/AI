Make more 
so i learned how to write a bigram verison of name generator based on train_set

The Neural network part is pretty simple

The forward passing depends on logits = one_hot_tensor @ W and softmax(logits)

what is softmax ? 

*simple* 
```python
counts = logits.exp()
probs = counts / counts.sum(1, keepdims=True)
```

But remember pytorch will delete the computing graph after running the backward function to save memory

remember to forward before backward

so what is bigram 

simple 

let's say hello's bigram is ['he', 'el', 'll', 'lo']

We are using the consecutive elements's appearance's probs to predict the name

简单来说就是用让模型知道一个字母跟在另外一个字母后面的概率,从而根据这个概率去sample

但这个模型预测效果不好 But simple



