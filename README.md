# EncryptX

EncryptX is a high-performance, chunk-based file encryption engine designed
for streaming large files with constant memory usage.

The project focuses on systems-level concerns such as streaming I/O,
failure handling, data integrity, and performance analysis rather than
cryptographic novelty.

## Core Properties

- Chunk-based streaming I/O (GB-scale files)
- Constant memory usage (single reusable buffer)
- Pluggable encryption strategies
- Per-chunk integrity validation
- Early failure on corruption
- Benchmark-driven performance analysis

## Non-Goals

- Designing new cryptographic algorithms
- Replacing standard crypto libraries
- Providing network or distributed storage (single-node engine)

## Status

🚧 Initial scaffolding. Core engine implementation in progress.
