# OpenClip: an open-source implementation of OpenAI’s Contrastive Language-Image Pre-training (CLIP) model

<https://github.com/mlfoundations/open_clip>

```python
import torch
from PIL import Image
import open_clip

"""
model, preprocess_train, preprocess_val = open_clip.create_model_and_transforms(
    "ViT-B-32", pretrained="laion2b_s34b_b79k"
)

model.eval()  # model in train mode by default, impacts some models with BatchNorm or stochastic depth active
tokenizer = open_clip.get_tokenizer("ViT-B-32")
"""

# https://huggingface.co/models?library=open_clip
model, preprocess_train, preprocess_val = open_clip.create_model_and_transforms(
    "ViT-B-32",
    pretrained=r"E:\Models\open_clip\open_clip_pytorch_model laion CLIP-ViT-B-32-laion2B-s34B-b79K.bin",
)
tokenizer = open_clip.get_tokenizer("ViT-B-32")

image = preprocess_val(
    Image.open(
        r"D:\Jackie\Art\Art-of-Algorithm\60_ai\ai_test\images\Mondrian_Blocks\Mondrian Blocks - Challenges in Purple 88.jpg"
    )
).unsqueeze(0)
text = tokenizer(["a diagram", "a dog", "a cat"])

with torch.no_grad(), torch.autocast("cuda"):
    image_features = model.encode_image(image)
    text_features = model.encode_text(text)
    image_features /= image_features.norm(dim=-1, keepdim=True)
    text_features /= text_features.norm(dim=-1, keepdim=True)

    text_probs = (100.0 * image_features @ text_features.T).softmax(dim=-1)

print("Label probs:", text_probs)  # prints: [[1., 0., 0.]]
```
