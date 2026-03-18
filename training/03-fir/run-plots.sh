#!/usr/bin/env bash
set -e

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
VENV_DIR="${ROOT_DIR}/training/.venv"
cd "${ROOT_DIR}"

echo "=== Ensuring Output Directories Exist ==="
OUTPUT_DIR="${ROOT_DIR}/build-training/training/svg"
mkdir -p "${OUTPUT_DIR}"

echo "=== Checking Python Virtual Environment ==="
if [ ! -d "${VENV_DIR}" ]; then
    echo "Creating new virtual environment..."
    python3 -m venv "${VENV_DIR}"
fi

echo "=== Activating Virtual Environment ==="
source "${VENV_DIR}/bin/activate"

echo "=== Installing Dependencies ==="
if [ -f "requirements.txt" ]; then
    pip install -r requirements.txt
else
    echo "Missing requirements.txt."
    exit 1
fi

echo "=== Running Plot example ==="
# Export pythonpath so dspplot can be found
export PYTHONPATH=$ROOT_DIR/dspplot/dspplot:$PYTHONPATH
echo "PYTHONPATH set to ${PYTHONPATH}"

cmake -S "${ROOT_DIR}" -B "${ROOT_DIR}/build-training" -DENABLE_TRAINING=ON -DENABLE_TESTS=OFF
cmake --build "${ROOT_DIR}/build-training" --target kfr_training_fir -- -j6

cd "${ROOT_DIR}/build-training/training/03-fir"
"./kfr_training_fir"

echo "Plots saved under ${OUTPUT_DIR}"
