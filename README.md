Here is a concise `README.md` for your project:

---

# Random Forest Classifier Benchmark

This project benchmarks Random Forest classifiers implemented in Python (scikit-learn) and C++ (single-threaded and multi-threaded), using the SDSS_DR18 dataset.

## Setup Instructions

### 1. Clone the Repository

```bash
git clone git@github.com:pedromontuani/RandomForests.git
cd RandomForests
```

### 2. Create and Activate a Virtual Environment

```bash
python3 -m venv venv
source venv/bin/activate
```

### 3. Install Python Requirements

```bash
pip install -r requirements.txt
```

### 4. Build the C++ `random_forest_wrapper`

- Ensure you have a C++ compiler (e.g., `g++`) and `pybind11` installed.
- Ensure you have Boost.Python libraries
- Build the wrapper (example using `setup.py`):

```bash
python setup.py build_ext --inplace
```

- Alternatively, if using CMake:

```bash
g++ -shared -fPIC cpp_random_forest/randon_forest_wrapper.cpp -o cpp_random_forest/randon_forest_wrapper.so -I/usr/include/python3[YOUR_PYTHON_SUFFIX] -lboost_python3 -fopenmp

```

### 5. Add the Wrapper to the Virtual Environment

- Copy the generated `random_forest_wrapper*.so` file to your virtual environment's `site-packages` directory or ensure it is in your project root so Python can import it.

Example (from project root):

```bash
cp random_forest_wrapper*.so venv/lib/python*/site-packages/
```

### 6. Reload you Virtual Environment

```bash
deactiv ate
source venv/bin/activate
```


### 6. Run the Notebooks

Open `evaluation.ipynb` or `classification.ipynb` in your preferred IDE (e.g., PyCharm, JupyterLab) and run the cells to perform benchmarking and analysis.

---

**Note:**
- Adjust build instructions if your wrapper uses a different build system.
- The dataset `data/SDSS_DR18.csv` must be present in the `data/` directory.
- For multi-threaded C++ execution, ensure your system supports the required threading libraries.