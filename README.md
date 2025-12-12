Machine Learning 的本质 = 从数据里学习一个函数，使它能把输入映射到目标输出，并在未见过的数据上表现好。


你有 输入 X（特征）

你有 输出 y（标签 / 目标）

你想找一个函数 f(X) ≈ y

并且在新的 X 上也预测得准

这才叫 ML。

But for NN 

We are trying to apply the data to the result

So the f(x) don't really matters  

The whole point is adjust the weight.

For 传统ML We use scikit-learn XGBoost, LightGBM

One-hot encoding = 用多个 0/1 特征表示一个类别特征，让传统机器学习模型能理解非数字信息。

traditional ml 

read data 

preprocessing the data(删除无用列, 填缺失值, 编码分类变量, 特征工程)

切分训练/验证集

选择模型
1. 线性模型
2. 树模型
3. 距离模型
4. SVM

训练模型（完全不需要手写 forward/backward）

传统 ML：直接 .fit()，底层全帮你搞定

评估模型（和 NN 一模一样）

调参（类似 NN 的 hyperparameter tuning）

导出结果

NN 

load the data 

preprocessing the data 

build build model

get the loss function (loss rate)

forward passing 

backward passing 

tune the parameters

get the accuracy rate

sampling (use the model )


| 项目 | Neural Networks (NN) | Traditional Machine Learning |
|------|------------------------|-------------------------------|
| 数据需求量 | 通常需要大量数据（几千到几百万） | 小数据即可（几十到几千） |
| 是否需要 One-Hot | 通常需要，但 embedding 更常见 | 需要（尤其是线性模型/SVM） |
| 特征工程 | 较少（模型自动学习特征） | 很多（手工特征工程很关键） |
| 模型解释性 | 差（黑箱） | 好得多（线性模型/树模型可解释） |
| 训练成本 | 高，需要 GPU | 低，CPU 足够 |
| 训练时间 | 几分钟到几小时 | 几毫秒到几秒 |
| 推理速度 | 较慢 | 通常更快 |
| 典型算法 | CNN、RNN、Transformer、MLP | Logistic Regression、SVM、kNN、Random Forest、XGBoost |
| 核心优化 | 反向传播 + 梯度下降 | 封装在 fit() 内，看不到 |
| 对离群点敏感度 | 可能很敏感 | 模型依赖（树模型不敏感） |
| 用途 | 图像、语音、文本、复杂模式 | Tabular data（表格数据）、结构化数据 |
| 工程难度 | 高 | 低 |
| 超参数数量 | 多 | 较少 |
| 是否容易过拟合 | 容易（参数太多） | 看模型（线性不容易，树容易） |
| 适合的数据类型 | 非结构化数据（图像/文本/音频） | 结构化数据（表格 CSV） |


Neural Network Training Process


| Step | Description |
|------|-------------|
| 1. Load Data | 读取数据（train / validation / test） |
| 2. Preprocess Data | 标准化、归一化、padding、tokenize、one-hot 等 |
| 3. Build Model | 定义网络结构（层、激活函数、forward pass） |
| 4. Choose Loss Function | classification 用 cross-entropy，regression 用 MSE |
| 5. Forward Pass | 输入 → 模型 → 输出 → 计算 loss |
| 6. Backward Pass | 反向传播计算梯度（autograd 自动完成） |
| 7. Update Parameters | 使用优化器（SGD、Adam）更新权重 |
| 8. Evaluate Metrics | 在验证集上计算 accuracy、loss 等 |
| 9. Inference / Sampling | 使用训练好的模型进行预测或生成 |


Traditional Machine Learning Training Process


| Step | Description |
|------|-------------|
| 1. Load Data | 读取 train / test 数据 |
| 2. Preprocess Data | 填补缺失值、one-hot encoding、标准化等 |
| 3. Select Features | 选择要用于训练的字段（Pclass, Sex, Fare 等） |
| 4. Choose Model | Logistic Regression / SVM / Decision Tree / RF / XGBoost |
| 5. Fit Model | 调用 model.fit(X_train, y_train)，内部自动优化 |
| 6. Evaluate Model | 在 test/val 上计算 accuracy、F1、AUC 等 |
| 7. Predict | 使用 model.predict() 做推理 |
